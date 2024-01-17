#pragma once
class Mesh
{
public:
	Mesh(string name);
	virtual ~Mesh();

	void AddMesh(ModelPart* part);
	void AddMaterial(Material* material);

	void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void RenderInstanced(int count);

	ModelPart* GetPart(UINT slot) { return _parts[slot]; }
	Material* GetMaterial(UINT slot) { return _materials[slot]; }
	string GetName() { return _name; }

	void SetName(string name) { _name = name; }
	void SetShader(wstring path);
	void SetShader(UINT slot, wstring path) { _materials[slot]->SetShader(path); }
protected:
	virtual void ReadMesh() abstract;

	string _name;
	vector<ModelPart*> _parts;
	vector<Material*> _materials;
};

