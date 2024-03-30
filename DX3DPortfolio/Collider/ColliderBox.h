#pragma once
class ColliderBox : public Collider
{
	friend class Physics;

	ColliderBox(Vector3 size);
	~ColliderBox();
public:
	struct Obb
	{
		Vector3 position;
		Vector3 axis[3];
		Vector3 halfSize;
	};


	bool Collision(IN Ray& ray, OUT Contact* contact) override;
	bool Collision(ColliderBox* other) override;
	bool Collision(ColliderSphere* other) override; 

	bool Block(ColliderBox* other) override;
	bool Block(ColliderSphere* other) override;

	Obb GetOBB();
	bool SeparatedAxis(Vector3 D, Vector3 axis, Obb myObb, Obb otherObb);

private:
	void CreateMesh() override;

	Vector3 _size;
};