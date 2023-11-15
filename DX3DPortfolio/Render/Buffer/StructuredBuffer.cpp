#include "framework.h"
#include "StructuredBuffer.h"

StructuredBuffer::StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride, UINT outputCount)
	:_inputData(inputData), _inputStride(inputStride), _inputCount(inputCount), _outputStride(outputStride), _outputCount(outputCount)
{
	CreateInput();
	CreateOutput();
	CreateSRV();
	CreateUAV();
	CreateResult();
}

StructuredBuffer::~StructuredBuffer()
{
	_input->Release();
	_output->Release();
	_srv->Release();
	_uav->Release();
	_result->Release();
}

void StructuredBuffer::Copy(void* data, UINT size)
{
	DC->CopyResource(_result, _output);

	D3D11_MAPPED_SUBRESOURCE subResource;

	DC->Map(_result, 0, D3D11_MAP_READ, 0, &subResource);

	memcpy(data, subResource.pData, size);

	DC->Unmap(_result, 0);
}

void StructuredBuffer::UpdateInput(void* data)
{
	DC->UpdateSubresource(_input, 0, nullptr, data, _inputStride, _inputCount);

	_srv->Release();

	CreateSRV();
}

void StructuredBuffer::SetSRV()
{
	DC->CSSetShaderResources(0, 1, &_srv);
}

void StructuredBuffer::SetUAV()
{
	DC->CSSetUnorderedAccessViews(0, 1, &_uav, nullptr);
}

void StructuredBuffer::CreateInput()
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc = {};

	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = _inputStride * _inputCount;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	desc.StructureByteStride = _inputStride;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = _inputData;

	DEVICE->CreateBuffer(&desc, &initData, &buffer);

	_input = (ID3D11Resource*)buffer;
}

void StructuredBuffer::CreateOutput()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC desc = {};

	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = _outputStride * _outputCount;
	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = _outputStride;

	DEVICE->CreateBuffer(&desc, nullptr, &buffer);

	_output = (ID3D11Resource*)buffer;
}

void StructuredBuffer::CreateSRV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)_input;

	D3D11_BUFFER_DESC desc = {};
	buffer->GetDesc(&desc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.NumElements = _inputCount;

	DEVICE->CreateShaderResourceView(buffer, &srvDesc, &_srv);
}

void StructuredBuffer::CreateUAV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)_output;

	D3D11_BUFFER_DESC desc = { };
	buffer->GetDesc(&desc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;
	uavDesc.Buffer.Flags = 0;
	uavDesc.Buffer.NumElements = _outputCount;

	DEVICE->CreateUnorderedAccessView(buffer, &uavDesc, &_uav);
}

void StructuredBuffer::CreateResult()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC desc = {};
	((ID3D11Buffer*)_output)->GetDesc(&desc);

	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.MiscFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	DEVICE->CreateBuffer(&desc, nullptr, &buffer);

	_result = (ID3D11Resource*)buffer;
}
