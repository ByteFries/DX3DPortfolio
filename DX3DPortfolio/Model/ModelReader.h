#pragma once
typedef VertexTextureNormalTangentBlend ModelVertex;

class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	void Render();
	void RenderInstanced(UINT instanceCount);

	void Debug();

	vector<Material*> GetMaterials() { return _materials; }
private:
	void ReadMeshes();
	void ReadMaterials();

	string _name;

	vector<Material*> _materials;
	vector<ModelMesh*> _meshes;
};

