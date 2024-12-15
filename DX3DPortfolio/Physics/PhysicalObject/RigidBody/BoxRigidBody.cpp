#include "framework.h"
#include "BoxRigidBody.h"

BoxRigidBody::BoxRigidBody(size_t id, BoxCollider* collider, PhysicalCalculator* calculator)
	:RigidBody(id, collider, calculator)
{
    _size = collider->GetSize();
	Initialize();
}

void BoxRigidBody::Initialize()
{
    float factor = (1.0f / 12.0f) * _mass;
    float ixx = factor * (_size.y * _size.y + _size.z * _size.z);
    float iyy = factor * (_size.x * _size.x + _size.z * _size.z);
    float izz = factor * (_size.x * _size.x + _size.y * _size.y);

    _inertia = {
        ixx, 0.0f, 0.0f,
        0.0f, iyy, 0.0f,
        0.0f, 0.0f, izz
    };
}
