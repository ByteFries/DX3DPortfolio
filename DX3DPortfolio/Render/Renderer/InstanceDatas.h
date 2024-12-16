#pragma once
#include "framework.h"

struct InstanceDataBase
{
	InstanceDataBase() {}

	virtual void* GetData() abstract;
	virtual size_t GetSize() abstract;
};

struct InstanceMatrixData : public InstanceDataBase
{
	InstanceMatrixData() {}

	InstanceMatrixData(XMMATRIX matrix)
	{
		data.matrix = matrix;
	}

	void* GetData()
	{
		return &data;
	}

	size_t GetSize()
	{
		return sizeof(data);
	}

	struct Data
	{
		XMMATRIX matrix;
	} data;
};

struct InstanceMatrixColorData : public InstanceDataBase
{

	InstanceMatrixColorData(){}

	InstanceMatrixColorData(XMMATRIX matrix, XMFLOAT4 color)
	{
		data.matrix = matrix;
		data.color = color;
	}

	~InstanceMatrixColorData()
	{}

	void* GetData()
	{
		return &data;
	}

	size_t GetSize()
	{
		return sizeof(data);
	}

	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
		XMFLOAT4 color = {0,0,0,1};
	} data;
};

struct InstanceMatrixTextureData : public InstanceDataBase
{
	InstanceMatrixTextureData() {}
	InstanceMatrixTextureData(XMMATRIX matrix, int texIndex)
	{
		data.matrix = matrix;
		data.textureIndex = texIndex;
	}

	void* GetData() override
	{
		return &data;
	}

	size_t GetSize() override
	{
		return sizeof(data);
	}

	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
		int textureIndex = 0;
	} data;
};

