#include "framework.h"
#include "ColliderSphere.h"

ColliderSphere::ColliderSphere(float radius, float sliceCount, float stackCount)
    :_radius(radius), _sliceCount(sliceCount), _stackCount(stackCount)
{
    _type = SPHERE;
    CreateMesh();
}

ColliderSphere::~ColliderSphere()
{
}

bool ColliderSphere::Collision(IN Ray& ray, OUT Contact* contact)
{
    return false;
}

bool ColliderSphere::Collision(ColliderBox* other)
{
    return false;
}

bool ColliderSphere::Collision(ColliderSphere* other)
{
    return false;
}


void ColliderSphere::CreateMesh()
{
	for (UINT i = 0; i < _stackCount + 1; i++)
	{
		float phi = XM_PI / _stackCount * i;

		for (UINT j = 0; j < _sliceCount + 1; j++)
		{
			float theta = XM_2PI / _sliceCount * j;

			Vertex vertex;

			vertex.pos.x = _radius * sin(phi) * cos(theta);
			vertex.pos.y = _radius * cos(phi);
			vertex.pos.z = _radius * sin(phi) * sin(theta);

			_vertices.push_back(vertex);
		}
	}

	for (UINT j = 0; j < _stackCount; j++)
	{
		for (UINT i = 0; i < _sliceCount; i++)
		{
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 1 + (_sliceCount + 1) * (j + 0));

			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 1));
		}
	}

	_mesh = new Mesh(_vertices, _indices);
}
