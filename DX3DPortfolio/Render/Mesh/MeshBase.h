#pragma once
class MeshBase
{
public:
	MeshBase(string name = "Main");
	virtual ~MeshBase();

	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void SetName(string name) { _name = name; }

	string GetName() { return _name; }
	size_t GetIndexSize() { return _indices.size(); }

	virtual bool ImportMeshData() abstract;

	template<typename T>
	void CreateBuffers(vector<T> vertices, vector<UINT> indices);
protected:
	string _name;

	vector<UINT> _indices;
	VertexBuffer* _vBuffer;
	IndexBuffer* _iBuffer;
};

template<typename T>
inline void MeshBase::CreateBuffers(vector<T> vertices, vector<UINT> indices)
{
	_vBuffer = new VertexBuffer(vertices);
	_iBuffer = new IndexBuffer(indices);

	_indices = indices;
}