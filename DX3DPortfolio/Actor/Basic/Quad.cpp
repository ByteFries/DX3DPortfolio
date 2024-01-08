#include "framework.h"
#include "Quad.h"

Quad::Quad(XMFLOAT2 size)
	:_size(size)
{
	CreateVertices();
}

Quad::~Quad()
{
	delete _mesh;
}

void Quad::Render()
{
	_wBuffer->SetVSBuffer(0);
	_mesh->Render();
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

	VertexTextureNormalTangentBlend v;

	v.pos = { -halfSize.x, +halfSize.y, 0.0f };
	v.uv = { 0,0 };
	v.normal = { 0,0,-1 };
	v.tangent = { 1,0,0 };
	_vertices.push_back(v);

	v.pos = { +halfSize.x, +halfSize.y, 0.0f };
	v.uv = { 1,0 };
	v.normal = { 0,0,-1 };
	v.tangent = { 1,0,0 };
	_vertices.push_back(v);
	
	v.pos = { -halfSize.x, -halfSize.y, 0.0f };
	v.uv = { 0,1 };
	v.normal = { 0,0,-1 };
	v.tangent = { 1,0,0 };
	_vertices.push_back(v);

	v.pos = { +halfSize.x, -halfSize.y, 0.0f };
	v.uv = { 1,1 };
	v.normal = { 0,0,-1 };
	v.tangent = { 1,0,0 };
	_vertices.push_back(v);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_indices.push_back(2);
	_indices.push_back(1);
	_indices.push_back(3);

	ModelPart* modelPart = new ModelPart();
	modelPart->CreateBuffers(_vertices, _indices);

	Material* material = new Material();
	material->SetShader(L"Default");

	modelPart->SetMaterialSlot(0);

	_mesh = new StaticMesh();
	_mesh->AddMesh(modelPart);
	_mesh->AddMaterial(material);
}
