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

	_parts.clear();
}

void StaticMesh::SetMesh(string path)
{
	ModelData data;
	ModelReader::ReadModel(data, path);
	_name = path;
	_parts = data.parts;
}

void StaticMesh::AddMesh(ModelPart* part)
{
	_parts.push_back(part);
}

void StaticMesh::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	for (ModelPart* part : _parts)
		part->Render(type);
}

void StaticMesh::RenderInstanced(int count)
{
	for (ModelPart* part : _parts)
		part->RenderInstanced(count);
}

void StaticMesh::SetShader(wstring path)
{
	for (ModelPart* part : _parts)
		part->GetMaterial()->SetShader(path);
}
