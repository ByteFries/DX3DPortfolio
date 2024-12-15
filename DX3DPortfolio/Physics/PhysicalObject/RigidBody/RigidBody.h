#pragma once
class RigidBody : public PhysicalObject
{
	friend class PhysicsManager;
public:
	void Update() override;

	void AddImpact(Collider::Contact contact) override;

	const Vector3& GetLocalVelocity() { return _localVelocity; }
	const Vector3& GetAngularVelocity() { return _angularVelocity; }
	const Quaternion& GetRotation() { return _rotation; }
	
	void AddMomentSum(Vector3 momentSum) { _momentSum += momentSum; }
	void SetMomentSum(Vector3 momentSum) { _momentSum = momentSum; }
	void SetAngularVelocity(Vector3 angularVelocity) { _angularVelocity = angularVelocity; }
	void SetRotation(Quaternion rot) { _rotation = rot; }
protected:
	RigidBody(size_t id, Collider* collider, PhysicalCalculator* calculator);
	~RigidBody();

	virtual void Initialize() abstract;
	void UpdateDynamics();

	Matrix3x3 _inertia;
	Matrix3x3 _inertiaInv;

	Vector3 _localVelocity = {0,0,0};
	Quaternion _rotation = {0,0,0,0};
	Vector3 _eularAngle = {0,0,0};
	Vector3 _momentSum = {0,0,0};
	Vector3 _angularVelocity = {0,0,0};
};

