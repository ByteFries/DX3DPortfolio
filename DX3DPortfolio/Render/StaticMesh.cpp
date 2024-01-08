#include "framework.h"
#include "StaticMesh.h"

StaticMesh::StaticMesh()
{
	_name = "None";
}

StaticMesh::~StaticMesh()
{
	for (ModelPart* part : _parts)
		delete part;

	for (Material* material : _materials)
		delete material;

	_parts.clear();

	_materials.clear();
}

void StaticMesh::SetMesh(string path)
{
	ModelData data;
	ModelReader::ReadModel(data, path);
	_name = path;
	_parts = data.parts;
	_materials = data.materials;
}

void StaticMesh::AddMesh(ModelPart* part)
{
	_parts.push_back(part);
}

void StaticMesh::AddMaterial(Material* material)
{
	_materials.push_back(material);
}

void StaticMesh::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	for (ModelPart* part : _parts)
	{
		_materials[part->GetMaterialSlot()]->IASetBuffer();
		part->Render(type);
	}
}

void StaticMesh::RenderInstanced(int count)
{
	for (ModelPart* part : _parts)
	{
		_materials[part->GetMaterialSlot()]->IASetBuffer();
		part->RenderInstanced(count);
	}
}

void StaticMesh::Update()
{
}

void StaticMesh::SetShader(wstring path)
{
	for (Material* mat : _materials)
		mat->SetShader(path);
}
