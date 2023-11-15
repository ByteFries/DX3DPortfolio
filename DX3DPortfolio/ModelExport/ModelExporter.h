#pragma once

class ModelExporter
{
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


	Clip* ReadClip(aiAnimation* animation);
	void WriteClip(Clip* clip, string file);

	void ReadKeyFrame(Clip* clip, aiNode* node, vector<ClipNode>& clipNodes);

private:
	string _name;

	Assimp::Importer* _importer;

	const aiScene* _scene;

	vector<MeshData*> _meshes;

	vector<string> _materialNames;
	vector<string> _meshNames;


	vector<NodeData*> _nodes;
	vector<BoneData*> _bones;

	map<string, UINT> _boneMap;

	UINT _boneCount = 0;
};
