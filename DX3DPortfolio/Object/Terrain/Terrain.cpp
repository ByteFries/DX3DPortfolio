#include "framework.h"
#include "Terrain.h"

Terrain::Terrain()
{
	_material = new Material();

	CreateVertices();

	_mesh = new Mesh(_vertices, _indices);

	_material->SetShader(L"Default");
	_material->SetDiffuseMap(L"_Texture/IMG/Wall.png");
	_material->SetSpecularMap(L"_Texture/IMG/Wall_specular.png");
	_material->SetNormalMap(L"_Texture/IMG/Wall_normal.png");

	_cShader = Shader::AddCS(L"Picking");
}

Terrain::~Terrain()
{
	delete _mesh;
	delete _material;
}

void Terrain::Update()
{
	Transform::Update();
}

void Terrain::Render()
{
	_mBuffer->SetVSBuffer(0);

	_mesh->IASetBuffer();
	_material->IASetBuffer();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

bool Terrain::Picking(Vector3 input, OUT Vector3* position)
{
	Ray ray = Camera::Get()->ScreenPointToRay(input);

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

void Terrain::CreateVertices()
{
	Texture* heightMap = Texture::Get(L"_Texture/HeightMap/HeightMap.png");

	vector<XMFLOAT4> pixels = heightMap->ReadPixels();

	_height = heightMap->GetSize().y;
	_width = heightMap->GetSize().x;

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