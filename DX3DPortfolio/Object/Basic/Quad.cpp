#include "framework.h"
#include "Quad.h"

Quad::Quad(XMFLOAT2 size)
	:_size(size)
{
	CreateVertices();
	_mesh = new Mesh(_vertices, _indices);
	_material = new Material();
	_material->SetShader(L"Texture");
	_material->SetTexture(L"_Texture/IMG/LighthouseScene.png");
}

Quad::~Quad()
{
	delete _mesh;
	delete _material;
}

void Quad::Render()
{
	_mBuffer->SetVSBuffer(0);

	_mesh->IASetBuffer();
	_material->IASetBuffer();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void Quad::Update()
{
	Transform::Update();
}

void Quad::CreateVertices()
{
	XMFLOAT2 halfSize;
	halfSize.x = _size.x * 0.5f;
	halfSize.y = _size.y * 0.5f;

	VertexTexture v;

	v.pos = { -halfSize.x, +halfSize.y, 0.0f };
	v.uv = { 0,0 };
	_vertices.push_back(v);
	v.pos = { +halfSize.x, +halfSize.y, 0.0f };
	v.uv = { 1,0 };
	_vertices.push_back(v);
	v.pos = { -halfSize.x, -halfSize.y, 0.0f };
	v.uv = { 0,1 };
	_vertices.push_back(v);
	v.pos = { +halfSize.x, -halfSize.y, 0.0f };
	v.uv = { 1,1 };
	_vertices.push_back(v);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_indices.push_back(2);
	_indices.push_back(1);
	_indices.push_back(3);
}
