#pragma once
struct Vector3
{
	Vector3() {}
	~Vector3() {}

	Vector3(int x, int y, int z)
		:x(x), y(y), z(z)
	{}

	Vector3(float x, float y, float z)
		:x(x), y(y), z(z)
	{}

	
	Vector3(XMVECTOR other)
	{
		x = XMVectorGetX(other);
		y = XMVectorGetY(other);
		z = XMVectorGetZ(other);
	}

	operator XMVECTOR()
	{
		return XMVectorSet(x,y,z,0.0f);
	}

	Vector3 GetNormalized()
	{
		return XMVector3Normalize(*this);
	}

	float Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	float x = 0;
	float y = 0;
	float z = 0;
};

