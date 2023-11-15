#include "framework.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(Vector3 size)
	:_size(size)
{
	_type = BOX;
	CreateMesh();
}

ColliderBox::~ColliderBox()
{
}

bool ColliderBox::Collision(IN Ray& ray, OUT Contact* contact)
{
	return false;
}

bool ColliderBox::Collision(ColliderBox* other)
{
	return false;
}

bool ColliderBox::Collision(ColliderSphere* other)
{
	return false;
}


ColliderBox::Obb ColliderBox::GetOBB()
{
	return Obb();
}

void ColliderBox::CreateMesh()
{
	Vector3 halfSize = _size * 0.5f;

	_vertices =
	{
		 { -halfSize.x, +halfSize.y, -halfSize.z },
		 { +halfSize.x, +halfSize.y, -halfSize.z },
		 { -halfSize.x, -halfSize.y, -halfSize.z },
		 { +halfSize.x, -halfSize.y, -halfSize.z },
		 { -halfSize.x, +halfSize.y, +halfSize.z },
		 { +halfSize.x, +halfSize.y, +halfSize.z },
		 { -halfSize.x, -halfSize.y, +halfSize.z },
		 { +halfSize.x, -halfSize.y, +halfSize.z }
	};

	_indices =
	{
		0,1, 2,3, 4,5, 6,7,
		0,4, 1,5, 2,6, 3,7,
		0,2, 1,3, 4,6, 5,7
	};

	_mesh = new Mesh(_vertices, _indices);
}
