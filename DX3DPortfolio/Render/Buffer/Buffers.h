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

class WorldBuffer : public ConstantBuffer
{
public:
	WorldBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.matrix = XMMatrixIdentity();
	}
	~WorldBuffer() {}

	void SetMatrix(XMMATRIX matrix)
	{
		_data.matrix = XMMatrixTranspose(matrix);
	}


private:
	struct Data
	{
		XMMATRIX matrix;
	}_data;
};

class CameraBuffer : public ConstantBuffer
{
public:
	CameraBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{

	}
	~CameraBuffer() {}

	void SetMatrix(XMMATRIX view, XMMATRIX pos)
	{
		_data.view = XMMatrixTranspose(view);
		_data.pos = XMMatrixTranspose(pos);
	}

private:
	struct Data
	{
		XMMATRIX view;
		XMMATRIX pos;
	}_data;
};



class MaterialBuffer : public ConstantBuffer
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

	void SetTexture(bool val)
	{
		_data.hasTexture = val;
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

	bool HasTexture()
	{
		return _data.hasTexture;
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

	float GetShininess()
	{
		return _data.shininess;
	}

	void SetShininess(float val)
	{
		_data.shininess = val;
	}

	void SetLightAffect(bool val)
	{
		_data.affectByLight = val;
	}

private:
	struct Data
	{
		XMFLOAT4 diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		XMFLOAT4 specularColor = { 0.1f, 0.1f, 0.1f, 0.1f };
		XMFLOAT4 ambientColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		XMFLOAT4 emissive = { 0,0,0,0 };

		int hasTexture = 0;
		int hasDiffuseMap = 0;
		int hasSpecularMap = 0;
		int hasNormalMap = 0;
		int hasAlphaMap = 0;

		float shininess = 1.0f;
		int affectByLight = true;
		float padding;
	}_data;
};

class ColorBuffer : public ConstantBuffer

{
public:
	ColorBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.color = {0,1,0,1};
	}

	~ColorBuffer() {}

	void SetColor(XMFLOAT4 color)
	{
		_data.color = color;
	}

private:
	struct Data
	{
		XMFLOAT4 color;
	} _data;
};