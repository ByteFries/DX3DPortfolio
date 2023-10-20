#include "framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT size)
	:_data(data), _size(size)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = size;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	DEVICE->CreateBuffer(&bufferDesc, nullptr, &_cBuffer);
}

ConstantBuffer::~ConstantBuffer()
{
	_cBuffer->Release();
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
	UpdateSubresource();
	DC->VSSetConstantBuffers(slot, 1, &_cBuffer);
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
	UpdateSubresource();
	DC->PSSetConstantBuffers(slot, 1, &_cBuffer);
}

void ConstantBuffer::UpdateSubresource()
{
	DC->Map(_cBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);

	memcpy(_subResource.pData, _data, _size);

	DC->Unmap(_cBuffer, 0);

}
