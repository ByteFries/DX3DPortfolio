#pragma once
class ColliderSphere : public Collider
{
public:
	ColliderSphere(float radius, float sliceCount, float stackCount);
	~ColliderSphere();

	bool Collision(IN Ray& ray, OUT Contact* contact) override;
	bool Collision(ColliderBox* other) override;
	bool Collision(ColliderSphere* other) override;

	bool Block(ColliderBox* other) override;
	bool Block(ColliderSphere* other) override;

	float GetRadius() { return _radius * max(_worldScale.x, max(_worldScale.y, _worldScale.z)); }

private:
	void CreateMesh() override;

	float _radius;
	float _sliceCount;
	float _stackCount;
};

