#pragma once
struct ModelData
{
	string meshName;
	vector<Material*> materials;
	vector<ModelPart*> parts;
	vector<NodeData> nodes;
	vector<BoneData> bones;
	map<string, UINT> boneMap;
};

struct ClipData
{
	string savePath;
	string name;
	UINT frameCount;
	float ticksPerSecond;
	float duration;
	unordered_map<string, vector<KeyTransform>> keyTransforms;
};

namespace ModelReader
{
	void ReadModel(class ModelData& data);
	void ReadMaterials(ModelData& data);
	void ReadModelParts(ModelData& data);
	void ReadClip(ClipData& data);
};