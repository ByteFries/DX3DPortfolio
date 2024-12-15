#pragma once
#include "Render\Mesh\MeshBase.h"
#include "Render\Material\Material.h"

struct ModelData
{
	string modelName;

	vector<Material*> materials;
	
	vector<MeshBase*> meshes;
	vector<NodeData> nodes;
	vector<BoneData> bones;
	map<string, UINT> boneMap;

	vector<UINT> materialIndices;
};

namespace ModelReader
{
	void ReadModel(class ModelData& data);
	void ReadMaterials(ModelData& data);
	void ReadMeshes(ModelData& data);
	void ReadClip(ClipData& data);
};