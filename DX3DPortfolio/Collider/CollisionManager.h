#pragma once
class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton;

	CollisionManager();
	~CollisionManager();
public:
	void Update();

	void Render();

	ColliderBox* CreateColliderBox(Vector3 size);

	ColliderSphere* CreateColliderSphere(float radius, float sliceCount, float stackCount);

	void Debug();

private:
	vector<Collider*> _colliders;

	bool _visible = false;
};

