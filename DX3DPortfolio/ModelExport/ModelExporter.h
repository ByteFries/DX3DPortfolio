#pragma once

class ModelExporter
{
	struct KeyFrame
	{
		string boneName;
	
		vector<KeyTransform> transforms;
	};

	struct ClipData
	{
		string name;
	
		UINT frameCount;
	
		float ticksPerSecond;
		float duration;
	
		vector<KeyFrame*> keyFrame;
	};

	struct ClipNode
	{
		aiString name;
	
		vector<KeyTransform> keyFrame;
	};

public:
	ModelExporter(string name);
	~ModelExporter();
	
	void ExportModel();
	void ExportClip(string file);

private:
	void ExportMaterial();
	void ExportMesh();

	wstring CreateTexture(string file);

	void ReadMesh(aiNode* node);
	void ReadNode(aiNode* node, int index, int parent);
	void ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights);

	void WriteMesh();

	ClipData* ReadClip(aiAnimation* animation);
	void WriteClip(ClipData* clip, string file);

	void ReadKeyFrame(ClipData* clip, aiNode* node, vector<ClipNode>& clipNodes);

private:
	string _name;

	Assimp::Importer* _importer;

	const aiScene* _scene;

	map<string, vector<MeshData*>> _meshes;

	vector<string> _materialNames;
	vector<string> _meshNames;


	vector<NodeData*> _nodes;
	vector<BoneData*> _bones;

	map<string, UINT> _boneMap;

	UINT _boneCount = 0;
};
