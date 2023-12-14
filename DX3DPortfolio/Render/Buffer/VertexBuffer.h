#pragma once
class VertexBuffer
{
public:
	template<class T>
	VertexBuffer(vector<T>& vertices);
	~VertexBuffer();

	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void InstancingSetBuffer(UINT slot = 1, D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	void UpdateVertices(void* data, UINT size);

private:
	ID3D11Buffer* _buffer;
	UINT _stride = 0;
	UINT _offset = 0;

	D3D11_MAPPED_SUBRESOURCE _subResource;
};

template<class T>
inline VertexBuffer::VertexBuffer(vector<T>& vertices)
{
	_stride = sizeof(T);
	_offset = 0;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = _stride * vertices.size();
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = vertices.data();

	DEVICE->CreateBuffer(&bufferDesc, &data, &_buffer);
}
