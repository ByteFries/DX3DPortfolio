#pragma once
class BoxRigidBody : public RigidBody
{
public:
	BoxRigidBody(size_t id, BoxCollider* collider, PhysicalCalculator* calculator);
	~BoxRigidBody() {}
private:
	void Initialize() override;
	Vector3 _size = {};
};

