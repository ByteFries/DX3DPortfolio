#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	DC->IASetPrimitiveTopology(type);
	DC->IASetVertexBuffers(0, 1, &_buffer, &_stride, &_offset);
}

void VertexBuffer::Update(void* data, UINT size)
{
	if (_bufferSize < size)
		return; //assert ÇÊ¿ä

	DC->UpdateSubresource(_buffer, 0, nullptr, data, 0, 0);
}