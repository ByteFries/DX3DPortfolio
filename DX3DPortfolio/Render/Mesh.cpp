#include "framework.h"
#include "Mesh.h"

Mesh::Mesh(string name)
	:_name(name)
{
}

Mesh::~Mesh()
{
	for (ModelPart* part : _parts)
		delete part;

	for (Material* material : _materials)
		delete material;

	_parts.clear();

	_materials.clear();
}

void Mesh::AddMesh(ModelPart* part)
{
	_parts.push_back(part);
}

void Mesh::AddMaterial(Material* material)
{
	_materials.push_back(material);
}

void Mesh::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	for (ModelPart* part : _parts)
	{
		_materials[part->GetMaterialSlot()]->IASetBuffer();
		part->Render(type);
	}
}

void Mesh::RenderInstanced(int count)
{
	for (ModelPart* part : _parts)
	{
		_materials[part->GetMaterialSlot()]->IASetBuffer();
		part->RenderInstanced(count);
	}
}

void Mesh::SetShader(wstring path)
{
	for (Material* mat : _materials)
		mat->SetShader(path);
}