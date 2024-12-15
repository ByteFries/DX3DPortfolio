#include "framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
    :_data(data), _dataSize(dataSize)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = dataSize;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &_buffer);
}

ConstantBuffer::~ConstantBuffer()
{
    _buffer->Release();
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
    UpdateSubresource();
    DC->VSSetConstantBuffers(slot, 1, &_buffer);
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    UpdateSubresource();
    DC->PSSetConstantBuffers(slot, 1, &_buffer);
}

void ConstantBuffer::UpdateSubresource()
{

    DC->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);

    memcpy(_subResource.pData, _data, _dataSize);

    DC->Unmap(_buffer, 0);
}
