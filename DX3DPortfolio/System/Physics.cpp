#include "framework.h"
#include "Physics.h"

Physics::Physics()
{
}

Physics::~Physics()
{
    for (Collider* collider : _colliders)
        delete collider;

    _colliders.clear();
}

void Physics::Update()
{
    for (Collider* collider : _colliders)
        collider->Update();
}

void Physics::Render()
{
    if (!_isVisible)
        return;

    for (Collider* collider : _colliders)
        collider->Render();
}

void Physics::Debug()
{

}

ColliderBox* Physics::CreateColliderBox(Vector3 size)
{
    ColliderBox* collider = new ColliderBox(size);

    _colliders.push_back(collider);

    return collider;
}

ColliderSphere* Physics::CreateColliderSphere(float radius, float sliceCount, float stackCount)
{
    ColliderSphere* collider = new ColliderSphere(radius, sliceCount, stackCount);

    _colliders.push_back(collider);

    return collider;
}
