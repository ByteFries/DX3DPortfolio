#include "framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(vector<UINT>& indices)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = indices.size() * sizeof(UINT);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = indices.data();

	DEVICE->CreateBuffer(&desc, &data, &_buffer);
}

IndexBuffer::~IndexBuffer()
{
	_buffer->Release();
}

void IndexBuffer::IASetBuffer()
{
	DC->IASetIndexBuffer(_buffer, DXGI_FORMAT_R32_UINT, 0);
}
