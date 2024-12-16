#include "framework.h"
#include "InstanceBuffer.h"

InstanceBuffer::InstanceBuffer(vector<InstanceDataBase*>& datas)
{
	if (datas.empty())
		return;
	
	D3D11_BUFFER_DESC bufferDesc = {};

	// Get raw data from instanceData
	//vector<void*> rawData;
	//
	//for (InstanceDataBase*& instance : datas)
	//{
	//	void* instanceData = malloc(instance->GetSize());
	//
	//	memcpy(instanceData, instance->GetData(), instance->GetSize());
	//
	//	rawData.push_back(instanceData);
	//}
	_stride = datas[0]->GetSize();
	_offset = 0;

	vector<BYTE> rawData;

	for (InstanceDataBase*& instance : datas)
	{
		size_t instanceSize = _stride;

		BYTE* instanceData = new BYTE[instanceSize];
		memcpy(instanceData, instance->GetData(), instanceSize);
	
		rawData.insert(rawData.end(), instanceData, instanceData + instanceSize);
		delete[] instanceData;
	}


	bufferDesc.ByteWidth = _stride * MAX_INSTANCE_COUNT;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = rawData.data();

	DEVICE->CreateBuffer(&bufferDesc, &data, &_buffer);

	//for (void* instanceData : rawData)
	//{
	//	free(instanceData);
	//}
}

InstanceBuffer::~InstanceBuffer()
{
}

void InstanceBuffer::Update(void* data, UINT size)
{
	if (_bufferSize < size)
		return;

	DC->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subresource);

	memcpy(_subresource.pData, data, size);

	DC->Unmap(_buffer, 0);
}

void InstanceBuffer::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	DC->IASetPrimitiveTopology(type);
	DC->IASetVertexBuffers(INSTANCE_BUFFER_SLOT, 1, &_buffer, &_stride, &_offset);
}
