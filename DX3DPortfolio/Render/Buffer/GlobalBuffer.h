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

	void SetAnimation(bool val)
	{
		_data.hasAnimation = val;
	}

	bool HasAnimation()
	{
		return _data.hasAnimation;
	}

private:
	struct Data
	{
		XMMATRIX matrix;
		int hasAnimation = 0;
		int padding[3];
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

class LightBuffer :public ConstantBuffer
{

public:
	struct LightData
	{
		XMFLOAT4 color = {1,1,1,1};

		Vector3 direction;
		int type;

		Vector3 position;
		float range;

		float inner;
		float outer;
		float length;
		int active;
	};

	LightBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.lights[0].direction = {0, -1, 0};
		_data.lights[0].type = 0;
		_data.lights[0].active = true;
		_data.lightCount = 1;
	}

	~LightBuffer() {}

private:
	struct Data
	{
		LightData lights[MAX_LIGHT];

		int lightCount;
		Vector3 ambientLight;
		Vector3 ambientCeil;
		int padding;
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

	int& HasDiffuseMapRef()
	{
		return _data.hasDiffuseMap;
	}

	int& HasSpecularMapRef()
	{
		return _data.hasSpecularMap;
	}

	int& HasNormalMapRef()
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

	XMFLOAT4& GetDiffuseColorRef()
	{
		return _data.diffuseColor;
	}
	XMFLOAT4& GetSpecularColorRef()
	{
		return _data.specularColor;
	}
	XMFLOAT4& GetAmbientColorRef()
	{
		return _data.ambientColor;
	}
	XMFLOAT4& GetEmissiveColorRef()
	{
		return _data.emissive;
	}

	float GetShininess()
	{
		return _data.shininess;
	}
	float& GetShininessRef()
	{
		return _data.shininess;
	}

	void SetLightAffect(bool val)
	{
		_data.affectByLight = val;
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
		float shininess;
		
		int affectByLight = true;
		Vector3 padding;
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

class FrameBuffer : public ConstantBuffer
{
public:
	FrameBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
		_data.next.clipIndex = -1;
	}

	struct Frame
	{
		int   clipIndex = 0;
		UINT  curFrame = 0;
		UINT  nextFrame = 0;
		float time = 0.0f;

		float speed = 1.0f;
		float padding3[3];
	};

	struct Data
	{
		float tweenTime = 0.0f;
		float runningTime = 0.0f;
		float padding1;
		float padding2;

		Frame cur, next;
	};

	const FrameBuffer::Frame GetCurFrame()
	{
		return _data.cur;
	}

	void SetCurFrame(Frame frame)
	{
		_data.cur = frame;
	}

	const FrameBuffer::Frame GetNextFrame()
	{
		return _data.next;
	}

	void SetNextFrame(Frame frame)
	{
		_data.next = frame;
	}

	FrameBuffer::Frame& GetCurFrameRef()
	{
		return _data.cur;
	}

	FrameBuffer::Frame& GetNextFrameRef()
	{
		return _data.next;
	}

	FrameBuffer::Data GetData()
	{
		return _data;
	}

	FrameBuffer::Data& GetDataRef()
	{
		return _data;
	}

	float GetTweenTime()
	{
		return _data.tweenTime;
	}

	float& GetTweenTimeRef()
	{
		return _data.tweenTime;
	}

	float GetRunningTime()
	{
		return _data.runningTime;
	}

	void SetTweenTime(float time)
	{
		_data.tweenTime = time;
	}

	void SetRunningTime(float time)
	{
		_data.runningTime = time;
	}

private:

	Data _data;
};

class InstancingFrameBuffer : public ConstantBuffer
{
public:
	InstancingFrameBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}

	struct Frame
	{
		int   clipIndex = 0;
		UINT  curFrame = 0;
		UINT  nextFrame = 0;
		float time = 0.0f;

		float speed = 1.0f;
		float padding3[3];
	};

	struct Motion
	{
		Motion()
		{
			next.clipIndex = -1;
		}

		float takeTime = 0.0f;
		float tweenTime = 0.0f;
		float runningTime = 0.0f;
		float padding = 0.0f;

		Frame cur, next;
	};

	struct Data
	{
		Motion motion[MAX_INSTANCE];
	} data;

	InstancingFrameBuffer::Motion& GetMotion(int index) { return _data.motion[index]; }

private:

	Data _data;
};
