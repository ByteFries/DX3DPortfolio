#include "framework.h"
#include "Collider.h"

bool Collider::_hidden = false;

Collider::Collider()
{
	_material = new Material();
	_material->SetShader(L"Collider");
	SetColor(0.0f, 1.0f, 0.0f);
}

Collider::~Collider()
{
	delete _mesh;
	delete _material;
}

void Collider::Render()
{
	if (_hidden)
		return;

	_mesh->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	_material->IASetBuffer();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

bool Collider::Collision(Collider* other)
{
	switch (other->_type)
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
