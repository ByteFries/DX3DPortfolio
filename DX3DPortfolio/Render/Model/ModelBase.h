#pragma once
class ModelBase : public ModelInterface
{
public:
	ModelBase(string name);
	virtual ~ModelBase();
	
	void SetShader(UINT index, wstring shaderName);
	void SetAllShader(wstring shaderName);
protected:
	string _name;
	vector<MeshBase*> _meshes;
	vector<UINT> _materialIndices;
	vector<Material*> _materials;
	vector<NodeData> _nodes;
};