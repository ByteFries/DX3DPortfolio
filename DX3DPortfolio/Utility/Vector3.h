#pragma once
#include "Matrix3x3.h"

struct Vector3
{
	Vector3() {}

	Vector3(float x, float y, float z) :x(x), y(y), z(z) {}

	Vector3(XMVECTOR value)
	{
		x = XMVectorGetX(value);
		y = XMVectorGetY(value);
		z = XMVectorGetZ(value);
	}

	Vector3(XMFLOAT3 value) :x(value.x), y(value.y), z(value.z) {}

	Vector3(const Vector3& other) :x(other.x), y(other.y), z(other.z) {}

	Vector3& operator=(const Vector3& other) 
	{ 
		this->x = other.x; 
		this->y = other.y; 
		this->z = other.z; 
		return *this;
	}

	operator XMVECTOR() { return XMVectorSet(x, y, z, 0.0f); }
	operator XMFLOAT3() { return XMFLOAT3(x, y, z); }

	Vector3 operator +(Vector3 other) { return Vector3(this->x + other.x, this->y + other.y, this->z + other.z); }
	Vector3 operator -(Vector3 other) { return Vector3(this->x - other.x, this->y - other.y, this->z - other.z); }
	Vector3 operator *(float value) { return Vector3(this->x * value, this->y * value, this->z * value); }
	Vector3 operator /(float value) { return Vector3(this->x / value, this->y / value, this->z / value); }

	Vector3 operator +(const Vector3 other) const { return Vector3(this->x + other.x, this->y + other.y, this->z + other.z); }
	Vector3 operator -(const Vector3 other) const { return Vector3(this->x - other.x, this->y - other.y, this->z - other.z); }
	Vector3 operator *(const float value) const { return Vector3(this->x * value, this->y * value, this->z * value); }
	Vector3 operator /(const float value) const { return Vector3(this->x / value, this->y / value, this->z / value); }

	friend Vector3 operator*(float scalar, const Vector3& vec) {
		return vec * scalar;
	}

	Vector3 operator*(const Matrix3x3& mat) const {
		return Vector3(
			mat.m[0][0] * x + mat.m[1][0] * y + mat.m[2][0] * z,
			mat.m[0][1] * x + mat.m[1][1] * y + mat.m[2][1] * z,
			mat.m[0][2] * x + mat.m[1][2] * y + mat.m[2][2] * z
		);
	}

	Vector3 operator-() const {
		return Vector3(-x, -y, -z);
	}

	bool operator==(const Vector3& other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool operator!=(const Vector3& other) const
	{
		return (x != other.x) || (y != other.y) || (z != other.z);
	}



	Vector3 operator+=(Vector3 other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vector3 operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}
	
	Vector3 operator/=(float value)
	{
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	Vector3 operator-=(Vector3 other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	bool operator<(const Vector3& v) const {
		if (x != v.x) return x < v.x;
		if (y != v.y) return y < v.y;
		return z < v.z;
	}

	static float Dot(Vector3 v1, Vector3 v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

	static Vector3 Cross(const Vector3& v1, const Vector3& v2)
	{
		return {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
		};
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float Length2() const
	{
		return x * x + y * y + z * z;
	}

	void Normalize()
	{
		float len = Length();

		x /= len;
		y /= len;
		z /= len;
	}

	Vector3 GetNormalized() const
	{
		Vector3 tmp = *this;
		return XMVector3Normalize(tmp);
	}

	//struct Hash
	//{
	//	std::size_t operator()(const Vector3& v) const
	//	{
	//		return std::hash<float>()(v.x) ^ std::hash<float>()(v.y) ^ std::hash<float>()(v.z);
	//	}
	//};

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

namespace std {
	template<>
	struct hash<Vector3> {
		std::size_t operator()(const Vector3& v) const 
		{
			return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1) ^ (std::hash<float>()(v.z) << 2);
		}
	};
}
