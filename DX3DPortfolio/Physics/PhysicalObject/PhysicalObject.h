#pragma once

namespace PhysicsType
{
	enum Behavior
	{
		STATIC = 0,
		LINEAR = 1 << 0, //  선운동 가능 (0001)
		ANGULAR = 1 << 1, //회전운동 가능 (0010)
	};

	enum CollisionHandling
	{
		NONE = 0,
		OVERLAP = 1 << 0,
		BLOCK = 1 << 1
	};
}

using namespace PhysicsType;

class PhysicalObject
{
public:
	

	void Render();
	virtual void Update(float delta);
	void UpdateWithForce();
	void UpdateVelocityFromMomentum();
	void UpdatePosAndRotation();
	
	void UpdateWithCollisionTime();
	void ApplyDamping();

	void SimulateTransform(shared_ptr<Shape>& shape, float delta) const;

	void SetShape(Shape* shape);
	void SetMass(float mass) { _mass = mass; }
	void SetPos(Vector3 pos) { _pos = pos; }
	void SetRotation(Quaternion quaternion) { _rotation = quaternion; }
	void SetRotation(Vector3 eular);
	void SetVelocity(Vector3 vel) { _velocity = vel; }
	void SetLocalVelocity(Vector3 vel) { _localVelocity = vel; }
	void SetAngularVelocity(Vector3 vel) { _angularVelocity = vel; }
	void SetLocalAngularVelocity(Vector3 vel) { _localAngularVelocity = vel; }
	void AddLinearMomentum(const Vector3& impulse) { _linearMomentum += impulse; }
	void AddAngularMomentum(const Vector3& impulse) { _angularMomentum += impulse; }


	void SetForce(Vector3 val) { _force = val; }

	void SetMomentSum(Vector3 moment) { _momentSum = moment; }

	void SetBehavior(int behavior) { _behaviorFlag = behavior; }
	void AddBehavior(int behavior) { _behaviorFlag = static_cast<Behavior>(_behaviorFlag | behavior); }
	void RemoveBehavior(int behavior) { _behaviorFlag = static_cast<Behavior>(_behaviorFlag & ~behavior); }

	void SetCollisionHandling(int handling) { _handlingFlag = handling; }
	void AddCollisionHandling(int handling) { _handlingFlag = static_cast<CollisionHandling>(_handlingFlag | handling); }
	void RemoveCollisionHandling(int handling) { _handlingFlag = static_cast<CollisionHandling>(_handlingFlag & ~handling); }

	void SetMaterial(MaterialProperty mat) { _material = mat; }

	const Vector3& GetPos() { return _pos; }
	const Vector3& GetForce() { return _force; }
	const Vector3& GetVelocity() { return _velocity; }
	const Vector3& GetLocalVelocity() { return _localVelocity; }
	const Vector3& GetAngularVelocity() { return _angularVelocity; }
	const Vector3& GetLocalAngularVelocity() { return _localAngularVelocity; }
	const Vector3& GetAcceleration() { return _acceleration; }
	const Vector3& GetLocalAngularAcceleration() { return _localAngularAcceleration; }
	const Vector3& GetMomentSum() { return _momentSum; }
	const Vector3& GetLinearMomentum() { return _linearMomentum; }
	const Vector3& GetAngularMomentum() { return _angularMomentum; }


	const Vector3& GetEular() { return _eularAngle; }
	const Quaternion& GetRotation() { return _rotation; }
	const Matrix3x3& GetInertia() { return _inertia; }
	const Matrix3x3& GetWorldInertiaInv() { return _worldInertiaInv; }

	float GetSpeed() { return _speed; }
	float GetMass() { return _mass; }
	int GetBehaviorFlag() { return _behaviorFlag;}
	int GetCollisionHandlingFlag() { return _handlingFlag; }
	Shape* GetShape() { return _shape; }
	Shape* GetShapeConst() const { return _shape; }
	UINT GetIndex() { return _index; }
	bool IsBehaviorFlagSet(Behavior flag) const;
	bool IsHandlingFlagSet(CollisionHandling flag) const;
	bool IsStatic() const { return _behaviorFlag == STATIC; }
	bool IsBlocking() const { return _handlingFlag & BLOCK; }
	MaterialProperty GetMaterial() { return _material; }

	void Initialize();
protected:	
	friend class PhysicsManager;

	PhysicalObject(UINT index, float mass); 
	virtual ~PhysicalObject();

	void UpdateLinearMotion(float delta);
	void UpdateAngularMotion(float delta);

	void UpdateLinearKinematics();
	void UpdateAngularKinematics();

	void ClampSmallVelocity(Vector3& velocity);

	int _behaviorFlag = 0;
	int _handlingFlag = 0;
	Shape* _shape;
	MaterialProperty _material = MaterialProperty::STONE;

	Quaternion _rotation = { 0,0,0,1 };
	Vector3 _pos = { 0,0,0 };

	Vector3 _velocity = {0,0,0};
	Vector3 _localVelocity = { 0,0,0 };
	Vector3 _acceleration = {0,0,0};

	Vector3 _angularVelocity = { 0,0,0 };
	Vector3 _localAngularVelocity = { 0,0,0 };
	Vector3 _angularAcceleration = {0,0,0};
	Vector3 _localAngularAcceleration = {0,0,0};
	Vector3 _eularAngle = { 0,0,0 };
	
	Vector3 _force = { 0,0,0 };
	Vector3 _momentSum = { 0,0,0 };
	Vector3 _linearMomentum = {0,0,0};
	Vector3 _angularMomentum = {0,0,0};

	float _speed = 0.0f;
	float _mass = 1.0f;

	Matrix3x3 _inertia;
	Matrix3x3 _inertiaInv;
	Matrix3x3 _worldInertiaInv; // impact 용

	UINT _index;
	bool _active = true;
};