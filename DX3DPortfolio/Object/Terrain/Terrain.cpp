#include "framework.h"
#include "Terrain.h"

Terrain::Terrain()
{
	_material = new Material();

	CreateVertices();

	_mesh = new Mesh(_vertices, _indices);

	_material->SetShader(L"Default");
	_material->SetTexture(L"_Texture/IMG/LighthouseScene.png");
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

void Terrain::CreateVertices()
{
	Texture* heightMap = Texture::Get(L"_Texture/HeightMap/HeightMap.png");

	vector<XMFLOAT4> pixels = heightMap->ReadPixels();

	_height = heightMap->GetSize().y;
	_width = heightMap->GetSize().x;

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			VertexTextureNormal v;
			v.pos = Vector3(j, 0, i);

			v.pos.y = pixels[i * _width + j].x * MAP_HEIGHT;

			v.uv.x = j / (_width - 1);
			v.uv.y = 1 - i / (_height - 1);

			_vertices.push_back(v);
		}
	}

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

	for (int i = 0; i < _indices.size() - 2; i += 2)
	{
		UINT index0 = _indices[i];
		UINT index1 = _indices[i + 1];
		UINT index2 = _indices[i + 2];

		VertexTextureNormal v0 = _vertices[index0];
		VertexTextureNormal v1 = _vertices[index1];
		VertexTextureNormal v2 = _vertices[index2];

		Vector3 v0to1 = (v1.pos - v0.pos).GetNormalized();
		Vector3 v0to2 = (v2.pos - v0.pos).GetNormalized();
		Vector3 normal = Vector3::Cross(v0to1, v0to2);

		_vertices[index0].normal += normal;
		_vertices[index1].normal += normal;
		_vertices[index2].normal += normal;
	}

}