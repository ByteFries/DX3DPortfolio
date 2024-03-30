#pragma once
class Physics : public Singleton<Physics>
{
	friend class Singleton;

	Physics();
	~Physics();

public:
	void Update();
	void Render();

	void Debug();

	ColliderBox* CreateColliderBox(Vector3 size);

	ColliderSphere* CreateColliderSphere(float radius, float sliceCount, float stackCount);

private:
	vector<Collider*> _colliders;

	bool _isVisible = false;
};

