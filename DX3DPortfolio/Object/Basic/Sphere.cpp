#include "framework.h"
#include "Sphere.h"


Sphere::Sphere(float _radius, UINT sliceCount, UINT stackCount)
	:_radius(_radius), _sliceCount(sliceCount), _stackCount(stackCount)
{
	CreateVertices();

	_mesh = new Mesh(_vertices, _indices);
	_material = new Material();

	_material->SetShader(L"Default");
}

Sphere::~Sphere()
{
	delete _mesh;
	delete _material;
}

void Sphere::Update()
{
	Transform::Update();
}

void Sphere::Render()
{
	_mBuffer->SetMatrix(_srt);
	_mBuffer->SetVSBuffer(0);

	_mesh->IASetBuffer();
	_material->IASetBuffer();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void Sphere::PostRender()
{
}

void Sphere::CreateVertices()
{
	for (int i = 0; i < _stackCount + 1; i++)
	{
		float phi = XM_PI / _stackCount * i;

		for (int j = 0; j < _sliceCount + 1; j++)
		{
			float theta = XM_2PI / _sliceCount * j;

			VertexTextureNormalMapping vertex;

			vertex.pos.x = _radius * sin(phi) * cos(theta);
			vertex.pos.y = _radius * cos(phi);
			vertex.pos.z = _radius * sin(phi) * sin(theta);

			vertex.normal = vertex.pos / _radius;

			vertex.uv.x = j / (float)_sliceCount;
			vertex.uv.y = i / (float)_stackCount;

			_vertices.push_back(vertex);
		}
	}

	for (UINT j = 0; j < _stackCount; j++)
	{
		for (UINT i = 0; i < _sliceCount; i++)
		{
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 1 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 1));

			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 1));
			_indices.push_back(i + 1 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 1 + (_sliceCount + 1) * (j + 1));
		}
	}

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
}
