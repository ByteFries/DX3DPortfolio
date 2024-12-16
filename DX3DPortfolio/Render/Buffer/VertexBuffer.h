#pragma once

class VertexBuffer : public DXBuffer
{
public:

	template<class T>
	VertexBuffer(std::vector<T>& data);	

	~VertexBuffer();

	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;

	void Update(void* data, UINT size) override;
};

template<class T>
inline VertexBuffer::VertexBuffer(std::vector<T>& vertices)
{
	D3D11_BUFFER_DESC bufferDesc = {};

	_stride = sizeof(T);
	_offset = 0;

	_bufferSize = _stride * vertices.size();

	bufferDesc.ByteWidth = _bufferSize;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = vertices.data();

	DEVICE->CreateBuffer(&bufferDesc, &data, &_buffer);
};
