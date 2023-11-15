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

class MaterialBuffer :public ConstantBuffer
{

public:
	MaterialBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
	}

	~MaterialBuffer() {}

	void SetDiffuseColor(float r, float g, float b, float alpha)
	{
		_data.diffuseColor = { r, g, b, alpha };
	}

	void SetSpecularColor(float r, float g, float b, float alpha)
	{
		_data.specularColor = { r, g, b, alpha };
	}

	void SetAmbientColor(float r, float g, float b, float alpha)
	{
		_data.ambientColor = { r, g, b, alpha };
	}

	void SetEmissiveColor(float r, float g, float b, float alpha)
	{
		_data.emissive = { r, g, b, alpha };
	}

	void SetDiffuseMap(bool val)
	{
		_data.hasDiffuseMap = val;
	}

	void SetSpecularMap(bool val)
	{
		_data.hasSpecularMap = val;
	}

	void SetNormalMap(bool val)
	{
		_data.hasNormalMap = val;
	}

	void SetShininess(int amount)
	{
		_data.shininess = amount;
	}

	bool HasDiffuseMap()
	{
		return _data.hasDiffuseMap;
	}

	bool HasSpecularMap()
	{
		return _data.hasSpecularMap;
	}

	bool HasNormalMap()
	{
		return _data.hasNormalMap;
	}

	XMFLOAT4 GetDiffuseColor()
	{
		return _data.diffuseColor;
	}
	XMFLOAT4 GetSpecularColor()
	{
		return _data.specularColor;
	}
	XMFLOAT4 GetAmbientColor()
	{
		return _data.ambientColor;
	}
	XMFLOAT4 GetEmissiveColor()
	{
		return _data.emissive;
	}

	int GetShininess()
	{
		return _data.shininess;
	}

private:
	struct Data
	{
		XMFLOAT4 diffuseColor = {1,1,1,1};
		XMFLOAT4 specularColor = {1,1,1,1};
		XMFLOAT4 ambientColor = {1,1,1,1};
		XMFLOAT4 emissive = { 0,0,0,1 };

		int hasDiffuseMap;
		int hasSpecularMap;
		int hasNormalMap;
		int shininess;
	} _data;
};

class RayBuffer : public ConstantBuffer
{
public:
	RayBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
	}

	float GetOutputSize()
	{
		return _data.outputSize;
	}

	Vector3 GetOrigin()
	{
		return _data.origin;
	}

	Vector3 GetDirection()
	{
		return _data.direction;
	}

	void SetOutputSize(float size)
	{
		_data.outputSize = size;
	}

	void SetOrigin(Vector3 origin)
	{
		_data.origin = origin;
	}

	void SetDirection(Vector3 direction)
	{
		_data.direction = direction;
	}

private:

	struct Data
	{
		float   outputSize = 0;
		Vector3 origin = {};
		Vector3 direction = {};
		float   padding = 0;
	} _data;
};