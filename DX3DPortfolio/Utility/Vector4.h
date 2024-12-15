#pragma once
#include "framework.h"

struct Vector4 {
    float x, y, z, w;

    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(Vector3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vector3 xyz() const { return Vector3(x, y, z); }

    float Length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Vector4 Normalize() const {
        float len = Length();
        if (len == 0) return *this; // 0 벡터의 경우, 정규화는 원래 벡터를 반환
        return *this / len;
    }

    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Vector4 operator/(float scalar) const {
        return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    float Dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }


};