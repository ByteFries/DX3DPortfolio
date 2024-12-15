#pragma once
struct Vector2
{
	Vector2() {}
	Vector2(float x, float y) :x(x), y(y) {}

	Vector2 operator +(Vector2 other) { return Vector2(this->x + other.x, this->y + other.y); }
	Vector2 operator -(Vector2 other) { return Vector2(this->x - other.x, this->y - other.y); }
	Vector2 operator *(float value) { return Vector2(this->x * value, this->y * value); }

	static float Dot(Vector2 v1, Vector2 v2) { return v1.x * v2.x + v1.y * v2.y; }

	float x = 0, y = 0;
};