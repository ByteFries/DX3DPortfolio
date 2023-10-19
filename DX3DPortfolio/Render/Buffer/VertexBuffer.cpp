#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	_buffer->Release();
}

void VertexBuffer::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	DC->IASetPrimitiveTopology(type);

	DC->IASetVertexBuffers(0, 1, &_buffer, &_stride, &_offset);
}

void VertexBuffer::UpdateVertices(void* data, UINT size)
{
	DC->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);

	memcpy(_subResource.pData, data, size);

	DC->Unmap(_buffer, 0);
}
