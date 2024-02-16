#include "framework.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	for (Collider* collider : _colliders)
		delete collider;

	_colliders.clear();
}

void CollisionManager::Update()
{
	for (Collider* collider : _colliders)
		collider->Update();


}

void CollisionManager::Render()
{
	if (!_visible)
		return;

	for (Collider* collider : _colliders)
		collider->Render();
}

ColliderBox* CollisionManager::CreateColliderBox(Vector3 size)
{
	ColliderBox* box = new ColliderBox(size);

	_colliders.push_back(box);

	return box;
}

ColliderSphere* CollisionManager::CreateColliderSphere(float radius, float sliceCount, float stackCount)
{
	ColliderSphere* sphere = new ColliderSphere(radius, sliceCount, stackCount);

	_colliders.push_back(sphere);

	return sphere;
}

void CollisionManager::Debug()
{

}
