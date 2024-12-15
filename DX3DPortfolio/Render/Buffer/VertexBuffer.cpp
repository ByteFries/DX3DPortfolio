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

void VertexBuffer::IASetBuffer(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type)
{
	DC->IASetPrimitiveTopology(type);
	DC->IASetVertexBuffers(slot, 1, &_buffer, &_stride, &_offset);
}

void VertexBuffer::Update(void* data, UINT size)
{
	if (_isDynamic)
	{
		DC->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subresource);

		memcpy(_subresource.pData, data, size);

		DC->Unmap(_buffer, 0);
	}
	else
	{
		DC->UpdateSubresource(_buffer, 0, nullptr, data, 0, 0);
	}
}
