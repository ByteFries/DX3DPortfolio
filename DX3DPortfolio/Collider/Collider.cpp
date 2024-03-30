#include "framework.h"
#include "Collider.h"

Collider::Collider()
{
}

Collider::~Collider()
{
	delete _mesh;
}

void Collider::Render()
{

	_wBuffer->SetVSBuffer(0);

	_mesh->Render(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	DC->DrawIndexed(_indices.size(), 0, 0);
}

bool Collider::Collision(Collider* other)
{
	switch (other->_colliderType)
	{
	case Collider::BOX:
		return Collision((ColliderBox*)other);
	case Collider::SPHERE:
		return Collision((ColliderSphere*)other);
	default:
		break;
	}

	return false;
}

bool Collider::Block(Collider* other)
{
	switch (other->_colliderType)
	{
	case Collider::BOX:
		return Block((ColliderBox*)other);
	case Collider::SPHERE:
		return Block((ColliderSphere*)other);
	default:
		break;
	}

	return false;
}