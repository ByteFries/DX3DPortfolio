#include "framework.h"
#include "ModelBase.h"

ModelBase::ModelBase(string name)
	:_name(name)
{
}

ModelBase::~ModelBase()
{
	for (MeshBase* mesh : _meshes)
		delete mesh;

	_meshes.clear();

	for (Material* material : _materials)
		delete material;

	_materials.clear();
}

void ModelBase::SetShader(UINT index, wstring shaderName)
{
	_materials[index]->SetShader(shaderName);
}

void ModelBase::SetAllShader(wstring shaderName)
{
	for (Material* mat : _materials)
		mat->SetShader(shaderName);
}
