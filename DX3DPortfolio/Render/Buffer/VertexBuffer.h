#pragma once

#include "Render/Renderer/InstanceDatas.h"
class VertexBuffer
{
public:

	template<class T>
	VertexBuffer(std::vector<T>& data, typename std::enable_if<std::is_base_of<InstanceDataBase, T>::value>::type* = 0);


	template<class T>
	VertexBuffer(std::vector<T>& data, typename std::enable_if<!std::is_base_of<InstanceDataBase, T>::value>::type* = 0);
	

	~VertexBuffer();

	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void IASetBuffer(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void Update(void* data, UINT size);
private:
	ID3D11Buffer* _buffer;
	UINT _stride = 0;
	UINT _offset = 0;
	bool _isDynamic = true;

	D3D11_MAPPED_SUBRESOURCE _subresource;
};

template<class T>
inline VertexBuffer::VertexBuffer(std::vector<T>& vertices, typename std::enable_if<std::is_base_of<InstanceDataBase, T>::value>::type*)
	:_isDynamic(false)
{
	D3D11_BUFFER_DESC bufferDesc = {};

	_stride = sizeof(T);
	_offset = 0;

	bufferDesc.ByteWidth = _stride * vertices.size();
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = vertices.data();

	DEVICE->CreateBuffer(&bufferDesc, &data, &_buffer);
};

template<class T>
inline VertexBuffer::VertexBuffer(std::vector<T>& data, typename std::enable_if<!std::is_base_of<InstanceDataBase, T>::value>::type*)
	:_isDynamic(false)
{
	if (data.empty())
		return;
	static_assert(std::is_base_of<InstanceDataBase, T>::value, "T must be a derived class of InstanceDataBase");

	D3D11_BUFFER_DESC bufferDesc = {};

	// Get raw data from instanceData
	vector<void*> rawData;
	for (InstanceDataBase& instance : data)
	{
		rawData.push_back(instance->GetData());
	}

	_stride = data[0]->GetSize();
	_offset = 0;

	bufferDesc.ByteWidth = _stride * MAX_INSTANCE_COUNT;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = rawData.data();

	DEVICE->CreateBuffer(&bufferDesc, &data, &_buffer);
}

