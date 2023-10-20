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