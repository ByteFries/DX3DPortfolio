#pragma once
#include "framework.h"

struct Quaternion
{
	
	Quaternion()
	{
		n = 1;
		v.x = 0;
		v.y = 0;
		v.z = 0;
	}

	Quaternion(float v1, float v2, float v3, float n)
	{
		v.x = v1;
		v.y = v2;
		v.z = v3;
		this->n = n;
	}

	~Quaternion() {}



	Quaternion(XMVECTOR value) 
	{
		v = value;
		n = XMVectorGetW(value);
	}

	operator XMVECTOR() { return XMVectorSet(v.x, v.y, v.z, n); }

	operator Vector3() { return v; }

	float Magnitude() { return (float)sqrt(n * n + v.x * v.x + v.y * v.y + v.z * v.z); }

	Vector3 GetVector() { return v; }
	float GetScalar() { return n; }

	Quaternion operator+=(Quaternion q)
	{
		v.x += q.v.x;
		v.y += q.v.y;
		v.z += q.v.z;
		n += q.n;

		return *this;
	}

	Quaternion operator-=(Quaternion q)
	{
		n -= q.n;
		v.x -= q.v.x;
		v.y -= q.v.y;
		v.z -= q.v.z;

		return *this;
	}

	Quaternion operator*=(float val)
	{
		n *= val;
		v.x *= val;
		v.y *= val;
		v.z *= val;

		return *this;
	}

	Quaternion operator/=(float val)
	{
		n /= val;
		v.x /= val;
		v.y /= val;
		v.z /= val;

		return *this;
	}

	Quaternion operator~() const 
	{ 
		float norm_squared = n * n + v.x * v.x + v.y * v.y + v.z * v.z;
		return Quaternion(-v.x / norm_squared, -v.y / norm_squared, -v.z / norm_squared, n / norm_squared);
	}

	Quaternion operator*(float s) {	return Quaternion(v.x * s, v.y * s, v.z * s, n * s);}
	
	Quaternion operator*(Vector3 v)
	{
		Quaternion q1 = { v.x, v.y, v.z, 0 };

		return (*this * q1);
	}

	Quaternion operator*(Quaternion q) 
	{	
		float new_n = n * q.n - v.x * q.v.x - v.y * q.v.y - v.z * q.v.z;

		Vector3 new_v = Vector3(
			n * q.v.x + q.n * v.x + v.y * q.v.z - v.z * q.v.y,
			n * q.v.y + q.n * v.y + v.z * q.v.x - v.x * q.v.z,
			n * q.v.z + q.n * v.z + v.x * q.v.y - v.y * q.v.x
		);

		return Quaternion(new_v.x, new_v.y, new_v.z, new_n);
	}

	float GetAngle()
	{
		return 2 * acos(n);
	}

	Vector3 GetAxis()
	{
		return v.GetNormalized();
	}

	Quaternion& GetNormalized() 
	{
		float mag = Magnitude();

		if (mag > 1e-6f) {  // Avoid division by zero or very small values
			n /= mag;
			v.x /= mag;
			v.y /= mag;
			v.z /= mag;
		}

		return *this;
	}

	void Normalize()
	{
		float mag = Magnitude();

		if (mag > 1e-6f) {
			n /= mag;
			v.x /= mag;
			v.y /= mag;
			v.z /= mag;
		}
	}

	static Quaternion Rotate(Quaternion q1, Quaternion q2)
	{
		return q1 * q2 * (~q1);
	}

	static Vector3 Rotate(Quaternion q, Vector3 v)
	{
		Quaternion new_q;

		new_q = q * v * (~q);

		return new_q.GetVector();
	}

	Vector3 toEulerAngles() const 
	{
		
		Vector3 euler;
		float sinr_cosp = 2 * (n * v.x + v.y * v.z);
		float cosr_cosp = 1 - 2 * (v.x * v.x + v.y * v.y);
		euler.x = std::atan2(sinr_cosp, cosr_cosp);

		float sinp = 2 * (n * v.y - v.z * v.x);
		euler.y = (std::fabs(sinp) >= 1) ? std::copysign(XM_PI / 2, sinp) : std::asin(sinp);

		float siny_cosp = 2 * (n * v.z + v.x * v.y);
		float cosy_cosp = 1 - 2 * (v.y * v.y + v.z * v.z);
		euler.z = std::atan2(siny_cosp, cosy_cosp);

		return euler;
	}

	static Matrix3x3 MakeMatrixFromQuaternion(Quaternion q)
	{
		Matrix3x3 result;

		float w = q.n;
		float x = q.v.x;
		float y = q.v.y;
		float z = q.v.z;

		result.m[0][0] = 1.0f - 2.0f * (y * y + z * z);
		result.m[0][1] = 2.0f * (x * y - z * w);
		result.m[0][2] = 2.0f * (x * z + y * w);

		result.m[1][0] = 2.0f * (x * y + z * w);
		result.m[1][1] = 1.0f - 2.0f * (x * x + z * z);
		result.m[1][2] = 2.0f * (y * z - x * w);

		result.m[2][0] = 2.0f * (x * z - y * w);
		result.m[2][1] = 2.0f * (y * z + x * w);
		result.m[2][2] = 1.0f - 2.0f * (x * x + y * y);

		return result;
	}

	static Quaternion FromAxisAndAngle(Vector3& axis, float angle)
	{
		Vector3 normalizedAxis = axis.GetNormalized();

		float halfAngle = angle * 0.5f;
		float sinHalfAngle = sin(halfAngle);

		Quaternion q;
		q.n = cos(halfAngle);
		q.v.x = normalizedAxis.x * sinHalfAngle;
		q.v.y = normalizedAxis.y * sinHalfAngle;
		q.v.z = normalizedAxis.z * sinHalfAngle;

		return q;
	}

	float n;
	Vector3 v;
};

