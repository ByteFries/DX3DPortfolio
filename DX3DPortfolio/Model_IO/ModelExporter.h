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

	void ExportAll();
	void ExportModel();
	void ExportClip(string file);

private:
	void ExportMaterial();
	void ExportMesh();

	wstring CreateTexture(string file);

	void ReadMesh();
	void ReadNode();
	void ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights);

	void WriteMesh();

	ClipData* ReadClip(aiAnimation* animation);
	void WriteClip(ClipData* clip, string file);

	void ReadKeyFrame(ClipData* clip, aiNode* node, vector<ClipNode>& clipNodes);

private:

	UINT GetMeshCount();

	string _name;

	Assimp::Importer* _importer;

	const aiScene* _scene;

	vector<string> _materialNames;
	vector<string> _meshNames;

	map<string, vector<MeshData*>> _meshes; //동일한 이름의 mesh가 존재할 수 도 있음.
	//vector<MeshData*> _meshes;
	vector<NodeData*> _nodes;
	vector<BoneData*> _bones;

	map<string, UINT> _boneMap;

	UINT _boneCount = 0;
};
