#include "framework.h"
#include "Terrain.h"

Terrain::Terrain(XMFLOAT2 size)
	:_width(size.x), _height(size.y)
{
	CreateVertices();

	_cShader = Shader::AddCS(L"Picking");
}

Terrain::Terrain(wstring HeightMap)
{
	_heightMap = Texture::Get(L"_Texture/HeightMap/HeightMap.png");

	_height = _heightMap->GetSize().y;
	_width = _heightMap->GetSize().x;

	CreateVertices();

	_cShader = Shader::AddCS(L"Picking");
}

Terrain::~Terrain()
{
	delete _mesh;
	delete _rBuffer;
	delete _sBuffer;
	delete _input;
	delete _output;
}

void Terrain::Update()
{
	Transform::Update();
}

void Terrain::Render()
{
	_wBuffer->SetVSBuffer(0);

	_mesh->Render();
}

bool Terrain::Picking(Vector3 input, OUT Vector3* position)
{
	Ray ray = MAIN_CAMERA->ScreenPointToRay(input);

	_rBuffer->SetOrigin(ray.origin);
	_rBuffer->SetDirection(ray.direction);
	_rBuffer->SetOutputSize(_polygonCount);

	_rBuffer->SetCSBuffer(0);

	_sBuffer->SetSRV();
	_sBuffer->SetUAV();

	_cShader->SetShader();

	UINT groupCount = ceil(_polygonCount / 1024.0f);

	DC->Dispatch(groupCount, 1, 1);

	_sBuffer->Copy(_output, sizeof(OutputDesc));

	float minDistance = FLT_MAX;

	for (UINT i = 0; i < _polygonCount; i++)
	{
		if (_output[i].isPicked)
		{
			if (minDistance > _output[i].distance)
			{
				minDistance = _output[i].distance;
			}
		}
	}

	if (minDistance < FLT_MAX)
	{
		*position = ray.origin + ray.direction * minDistance;

		return true;
	}

	return false;
}

bool Terrain::GetHeight(Vector3 pos, float& height)
{
	pos.x /= _scale.x;
	pos.z /= _scale.z;

	int x = (int)pos.x;
	int z = (int)pos.z;

	if (x < 0.0f || x >= _width)
		return false;
	if (z < 0.0f || z >= _height)
		return false;

	UINT indices[4];

	indices[0] = x + 0 + _width * (z + 1);
	indices[1] = x + 1 + _width * (z + 1);
	indices[2] = x + 0 + _width * (z + 0);
	indices[3] = x + 1 + _width * (z + 0);

	Vector3 vertices[4] = {};

	for (int i = 0; i < 4; i++)
	{
		vertices[i] = _vertices[indices[i]].pos;
	}

	float u = pos.x - vertices[0].x;
	float v = pos.z - vertices[0].z;

	Vector3 result;

	if (u + v <= 1.0f)
	{
		result = vertices[0] + (vertices[2] - vertices[0]) * u + (vertices[1] - vertices[0]) * v;
	}
	else
	{
		result = vertices[3] + (vertices[2] - vertices[3]) * (1 - u) + (vertices[1] - vertices[3]) * (1 - v);
	}

	height = result.y * _scale.y;

	return true;
}

void Terrain::CreateVertices()
{
	vector<XMFLOAT4> pixels;

	if (_heightMap)
	{
		pixels = _heightMap->ReadPixels();
	}
	else
		pixels.resize(_height * _width, XMFLOAT4(0,0,0,0));

	//////////////////////vertex///////////////////////////

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			VertexTextureNormalMapping v;
			v.pos = Vector3(j, 0, i);

			v.pos.y = pixels[i * _width + j].x * MAP_HEIGHT;

			v.uv.x = j / (_width - 1);
			v.uv.y = 1 - i / (_height - 1);

			_vertices.push_back(v);
		}
	}
	//////////////////////vertex///////////////////////////
	//////////////////////index///////////////////////////

	for (int i = 0; i < _height - 1; i++)
	{
		for (int j = 0; j < _width - 1; j++)
		{
			int index1 = (_width * (i + 1)) + (j + 0);
			int index2 = (_width * (i + 1)) + (j + 1);
			int index3 = (_width * (i + 0)) + (j + 0);
			int index4 = (_width * (i + 0)) + (j + 1);

			_indices.push_back(index1);
			_indices.push_back(index2);
			_indices.push_back(index3);

			_indices.push_back(index3);
			_indices.push_back(index2);
			_indices.push_back(index4);
		}
	}
	//////////////////////index///////////////////////////
	//////////////////////normal///////////////////////////

	for (int i = 0; i < _indices.size() - 2; i += 2)
	{
		UINT index0 = _indices[i];
		UINT index1 = _indices[i + 1];
		UINT index2 = _indices[i + 2];

		VertexTextureNormalMapping v0 = _vertices[index0];
		VertexTextureNormalMapping v1 = _vertices[index1];
		VertexTextureNormalMapping v2 = _vertices[index2];

		Vector3 v0to1 = (v1.pos - v0.pos).GetNormalized();
		Vector3 v0to2 = (v2.pos - v0.pos).GetNormalized();
		Vector3 normal = Vector3::Cross(v0to1, v0to2);

		_vertices[index0].normal += normal;
		_vertices[index1].normal += normal;
		_vertices[index2].normal += normal;
	}
	//////////////////////normal///////////////////////////
	//////////////////////tangent///////////////////////////

	for (UINT i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		Vector3 p0 = _vertices[index0].pos;
		Vector3 p1 = _vertices[index1].pos;
		Vector3 p2 = _vertices[index2].pos;

		XMFLOAT2 uv0 = _vertices[index0].uv;
		XMFLOAT2 uv1 = _vertices[index1].uv;
		XMFLOAT2 uv2 = _vertices[index2].uv;

		Vector3 dir01 = p1 - p0;
		Vector3 dir02 = p2 - p0;

		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;

		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		float D = 1.0f / (u1 * v2 - v1 * u2);

		Vector3 tangent = D * (dir01 * v2 - dir02 * v1);

		_vertices[index0].tangent += tangent;
		_vertices[index1].tangent += tangent;
		_vertices[index2].tangent += tangent;
	}

	for (VertexTextureNormalMapping& vertex : _vertices)
	{
		Vector3 T = vertex.tangent;
		Vector3 N = vertex.normal;

		vertex.tangent = (T - N * Vector3::Dot(N, T)).GetNormalized();
	}

	//////////////////////tangent///////////////////////////

	ModelPart* part = new ModelPart();
	part->CreateBuffers(_vertices, _indices);

	Material* material = new Material();
	material->SetShader(L"Default");
	part->SetMaterial(material);

	_mesh = new StaticMesh();
	_mesh->AddMesh(part);
}

void Terrain::CreateCompute()
{
	_polygonCount = _indices.size() / 3;

	if (_input != nullptr)
		delete[] _input;

	_input = new InputDesc[_polygonCount];

	for (UINT i = 0; i < _polygonCount; i++)
	{
		_input[i].index = i;

		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		_input[i].v0 = _vertices[index0].pos;
		_input[i].v1 = _vertices[index1].pos;
		_input[i].v2 = _vertices[index2].pos;
	}

	if (_sBuffer != nullptr)
		delete _sBuffer;

	_sBuffer = new StructuredBuffer
	{
		_input,
		sizeof(InputDesc),
		_polygonCount,
		sizeof(OutputDesc),
		_polygonCount
	};

	if (_output)
		delete[] _output;

	_output = new OutputDesc[_polygonCount];
}