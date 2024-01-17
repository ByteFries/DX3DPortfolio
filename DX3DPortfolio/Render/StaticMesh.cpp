#include "framework.h"
#include "StaticMesh.h"

StaticMesh::StaticMesh(string name)
	:Mesh(name)
{
	ReadMesh();
}

StaticMesh::StaticMesh()
	:Mesh("")
{
}

StaticMesh::~StaticMesh()
{
}


void StaticMesh::ReadMesh()
{
	if (_name == "")
		return;
	
	ModelData data;
	data.meshName = _name;

	ModelReader::ReadModel(data);

	_parts = data.parts;
	_materials = data.materials;

	SetShader(L"Default");
}
