#include "framework.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(Vector3 size)
	:_size(size)
{
	_colliderType = BOX;
	CreateMesh();
}

ColliderBox::~ColliderBox()
{
}

bool ColliderBox::Collision(IN Ray& ray, OUT Contact* contact)
{
	Contact temp;

	temp.distance = FLT_MAX;

	UINT faces[] =
	{
		0, 1, 2, 3,
		4, 5, 6, 7,
		1, 5, 3, 7,
		0, 4, 2, 6,
		0, 1, 4, 5,
		2, 3, 6, 7
	};

	for (UINT i = 0; i < 6; i++)
	{
		Vector3 p[4];

		for (UINT j = 0; j < 4; j++)
		{
			p[j] = _vertices[faces[4 * i + j]].pos;
			p[j] = XMVector3TransformCoord(p[j], _srt);
		}

		float distance = 0.0f;

		if (TriangleTests::Intersects(ray.origin, ray.direction, p[0], p[1], p[2], distance))
		{
			if (temp.distance > distance)
			{
				temp.distance = distance;
				temp.hitPoint = ray.origin + ray.direction * distance;
			}
		}

		if (TriangleTests::Intersects(ray.origin, ray.direction, p[3], p[1], p[2], distance))
		{
			if (temp.distance > distance)
			{
				temp.distance = distance;
				temp.hitPoint = ray.origin + ray.direction * distance;
			}
		}
	}

	if (temp.distance == FLT_MAX)
		return false;

	if (contact != nullptr)
		*contact = temp;

	return true;
}


bool ColliderBox::Collision(ColliderBox* other)
{
	Obb myObb = this->GetOBB();
	Obb otherObb = other->GetOBB();

	Vector3 direction = otherObb.position - myObb.position;

	for (UINT i = 0; i < 3; i++)
	{
		if (SeparatedAxis(direction, myObb.axis[i], myObb, otherObb))return false;
		if (SeparatedAxis(direction, otherObb.axis[i], myObb, otherObb))return false;
	}

	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			if (myObb.axis[i] == otherObb.axis[j]) return true;
		}
	}

	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			Vector3 cross = Vector3::Cross(myObb.axis[i], otherObb.axis[j]);

			if (SeparatedAxis(direction, cross, myObb, otherObb)) return false;
		}
	}

	return true;
}

bool ColliderBox::Collision(ColliderSphere* other)
{
	Obb box = this->GetOBB();

	Vector3 pos = box.position;

	for (UINT i = 0; i < 3; i++)
	{
		float length = Vector3::Dot(box.axis[i], this->_worldTranslation - other->GetWorldPos());

		float mult = (length < 0.0f) ? -1.0f : 1.0f;

		length = min(abs(length), box.halfSize[i]);

		pos += box.axis[i] * length * mult;
	}

	float distance = (pos - other->GetWorldPos()).Length();

	return distance <= other->GetRadius();
}


ColliderBox::Obb ColliderBox::GetOBB()
{
	Obb obb = {};

	obb.axis[0] = _right;
	obb.axis[1] = _up;
	obb.axis[2] = _forward;

	obb.halfSize = _size * 0.5f * _worldScale;

	obb.position = _worldTranslation;

	return obb;
}

bool ColliderBox::SeparatedAxis(Vector3 D, Vector3 axis, Obb myObb, Obb otherObb)
{
	float distance = abs(Vector3::Dot(D, axis));

	float sum = 0.0f;

	for (UINT i = 0; i < 3; i++)
	{
		sum += abs(Vector3::Dot(myObb.axis[i] * otherObb.halfSize[i], axis));
		sum += abs(Vector3::Dot(myObb.axis[i] * otherObb.halfSize[i], axis));
	}

	return distance > sum;
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

	ModelPart* part = new ModelPart();
	part->CreateBuffers(_vertices, _indices);

	Material* material = new Material();
	material->SetShader(L"Collider");
	material->GetMaterialBuffer()->SetDiffuseColor(0.0f, 1.0f, 0.0f, 0.0f);

	part->SetMaterialSlot(0);

	_mesh = new StaticMesh();
	_mesh->AddMesh(part);
	_mesh->AddMaterial(material);
}

bool ColliderBox::Block(ColliderBox* other)
{
	return false;
}

bool ColliderBox::Block(ColliderSphere* other)
{
	return false;
}
