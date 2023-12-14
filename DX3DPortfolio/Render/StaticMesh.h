#pragma once
class StaticMesh
{
public:
	StaticMesh();
	virtual ~StaticMesh();
	
	void SetMesh(string path);
	void AddMesh(ModelPart* part);

	virtual void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	virtual void RenderInstanced(int count);
	
	ModelPart* GetPart(UINT slot) { return _parts[slot]; }
	string GetName() { return _name; }

	void SetName(string name) { _name = name; }
	void SetShader(wstring path);
	void SetShader(UINT slot, wstring path) { _parts[slot]->GetMaterial()->SetShader(path); }
protected:
	string _name;
	vector<ModelPart*> _parts;
};
