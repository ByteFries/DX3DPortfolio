#pragma once
class Mesh
{
public:
	template<typename T>
	Mesh(vector<T>& vertices, vector<UINT>& indices);
	~Mesh();

	void UpdateVertices(void* data, UINT size);

	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

private:
	VertexBuffer* _vBuffer;
	IndexBuffer* _iBuffer;
};

template<typename T>
inline Mesh::Mesh(vector<T>& vertices, vector<UINT>& indices)
{
	_vBuffer = new VertexBuffer(vertices);
	_iBuffer = new IndexBuffer(indices);
}
