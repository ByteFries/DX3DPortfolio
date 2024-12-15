#include "framework.h"
#include "SkeletalModel.h"

SkeletalModel::SkeletalModel(string name)
	:ModelBase(name)
{
}

SkeletalModel::~SkeletalModel()
{
}

void SkeletalModel::Render()
{
	for (int i = 0; i < _meshes.size(); i++)
	{
		_meshes[i]->IASetBuffer();
		_materials[_materialIndices[i]]->IASetBuffer();
		DC->DrawIndexed(_meshes[i]->GetIndexSize(), 0, 0);
	}
}

void SkeletalModel::ReadModelData()
{
	ModelData data;
	data.modelName = _name;

	ModelReader::ReadModel(data);

	_boneMap = data.boneMap;
	_bones = data.bones;
	_materialIndices = data.materialIndices;
	_materials = data.materials;
	_meshes = data.meshes;
	_nodes = data.nodes;
}
