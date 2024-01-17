#include "framework.h"
#include "SkeletalMesh.h"

SkeletalMesh::SkeletalMesh(string name)
	:Mesh(name)
{
	ReadMesh();
}

SkeletalMesh::~SkeletalMesh()
{
}

void SkeletalMesh::ReadMesh()
{
	ModelData data;
	data.meshName = _name;

	ModelReader::ReadModel(data);

	_parts = data.parts;
	_materials = data.materials;
	_bones = data.bones;
	_boneMap = data.boneMap;
	_nodes = data.nodes;

	SetShader(L"Default");
}
