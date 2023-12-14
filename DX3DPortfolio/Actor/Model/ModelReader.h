#pragma once
struct ModelData
{
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
	unordered_map<string, KeyFrame*> keyFrames;
};

namespace ModelReader
{
	void ReadModel(class ModelData& data, string name);
	void ReadMaterials(ModelData& data, string name);
	void ReadModelParts(ModelData& data, string name);
	void ReadClip(ClipData& data);
};