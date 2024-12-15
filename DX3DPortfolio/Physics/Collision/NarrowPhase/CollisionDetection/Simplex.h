#pragma once
#include "framework.h"
#include <array>
#include <initializer_list>

#define VERTA 0
#define VERTB 1
#define VERTC 2
#define VERTD 3


class Simplex
{
public:
	Simplex() :_size(0) {}

	Simplex& operator=(std::initializer_list<Vector3> points)
	{
		_size = 0;

		for (Vector3 point : points)
			_points[_size++] = point;

		return *this;
	}

	void Push_front(Vector3 point)
	{
		_points = { point, _points[0], _points[1] , _points[2] };
		_size = min(_size + 1, 4);
	}

	void Clear()
	{
		_points = {};
		_size = 0;
	}

	Vector3& operator[](int i) { return _points[i]; }
	size_t size() const { return _size; }

	std::array<Vector3, 4>::const_iterator Begin() const { return _points.begin(); }
	std::array<Vector3, 4>::const_iterator End() const { return _points.end(); }
private:

	std::array<Vector3, 4> _points;
	UINT _size;
};

