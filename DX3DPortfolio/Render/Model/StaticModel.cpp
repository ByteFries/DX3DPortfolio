#include "framework.h"
#include "StaticModel.h"

StaticModel::StaticModel(string name)
	:ModelBase(name)
{
}

StaticModel::~StaticModel()
{
}

void StaticModel::Render()
{
	for (int i = 0; i < _meshes.size(); i++)
	{
		_meshes[i]->IASetBuffer();
		_materials[_materialIndices[i]]->IASetBuffer();
		DC->DrawIndexed(_meshes[i]->GetIndexSize(), 0, 0);
	}
}

void StaticModel::ReadModelData()
{
	ModelData data;
	data.modelName = _name;

	ModelReader::ReadModel(data);

	_materialIndices = data.materialIndices;
	_materials = data.materials;
	_meshes = data.meshes;
	_nodes = data.nodes;
}
