#pragma once
class MatrixBuffer : public ConstantBuffer
{
public:
	MatrixBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.matrix = XMMatrixIdentity();
	}
	~MatrixBuffer() {}

	void SetMatrix(XMMATRIX matrix)
	{
		_data.matrix = XMMatrixTranspose(matrix);
	}

private:
	struct Data
	{
		XMMATRIX matrix;
	} _data;
};

class CameraBuffer : public ConstantBuffer
{
public:
	CameraBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.view = XMMatrixIdentity();
		_data.pos = XMMatrixIdentity();
	}
	~CameraBuffer() {}

	void SetMatrix(XMMATRIX view, XMMATRIX pos)
	{
		_data.view = XMMatrixTranspose(view);
		 _data.pos =  XMMatrixTranspose(pos);
	}

private:
	struct Data
	{
		XMMATRIX view;
		XMMATRIX pos;
	} _data;
};


class ColorBuffer :public ConstantBuffer
{
	
public:
	ColorBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.color = {1.0f, 1.0f, 1.0f, 1.0f};
	}
	~ColorBuffer() {}

	void SetMatrix(XMFLOAT4 color)
	{
		_data.color = color;
	}

private:
	struct Data
	{
		XMFLOAT4 color;
	} _data;
};

class SunBuffer :public ConstantBuffer
{

public:
	SunBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.L = {0, 1, 0};
	}

	~SunBuffer() {}

	void SetDirection(Vector3 direction)
	{
		_data.L = -direction.GetNormalized();
	}

private:
	struct Data
	{
		Vector3 L;
		float padding;
	} _data;
};