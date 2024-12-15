#include "framework.h"
#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(UINT index, float mass)
	:_index(index), _mass(mass)
{	
}

PhysicalObject::~PhysicalObject()
{
	delete _shape;
}

bool PhysicalObject::IsBehaviorFlagSet(Behavior flag) const
{
	return (_behaviorFlag & flag) != 0;
}

bool PhysicalObject::IsHandlingFlagSet(CollisionHandling flag) const
{
	return (_handlingFlag & flag) != 0;
}

void PhysicalObject::Initialize()
{
	_velocity = { 0,0,0 };
	_localVelocity = { 0,0,0 };
	_acceleration = { 0,0,0 };
	_force = { 0,0,0 };
	_momentSum = { 0,0,0 };
	_angularVelocity = { 0,0,0 };
	_localAngularVelocity = { 0,0,0 };
	_angularAcceleration = { 0,0,0 };
	_localAngularAcceleration = { 0,0,0 };
	_eularAngle = { 0,0,0 };
}

void PhysicalObject::Render()
{
	_shape->Render();
}

void PhysicalObject::Update(float delta)
{
	if (IsBehaviorFlagSet(LINEAR))
		UpdateLinearMotion(delta);

	if (IsBehaviorFlagSet(ANGULAR))
		UpdateAngularMotion(delta);

	_shape->UpdateTransform(_pos, _eularAngle);
}

void PhysicalObject::UpdateWithForce()
{
	if (IsBehaviorFlagSet(LINEAR))
		UpdateLinearKinematics();

	if (IsBehaviorFlagSet(ANGULAR))
		UpdateAngularKinematics();
}

void PhysicalObject::UpdateWithCollisionTime()
{
	/*
	if (IsHandlingFlagSet(BLOCK))
	{
		Update(_collisionTime);
		_force = {0,0,0};
		_momentSum = {0,0,0};
	}
	*/
}

void PhysicalObject::UpdateLinearMotion(float delta)
{
	_acceleration = _force / _mass;

	_velocity += _acceleration * delta;

	//ClampSmallVelocity(_velocity);

	_pos += _velocity * delta;
}

void PhysicalObject::UpdateAngularMotion(float delta)
{
	Vector3 gyroEffect = Vector3::Cross(_localAngularVelocity, (_inertia * _localAngularVelocity));

	_localAngularAcceleration = _inertiaInv * (_momentSum - gyroEffect);

	_localAngularVelocity += _localAngularAcceleration * delta;

	//ClampSmallVelocity(_localAngularVelocity);

	Quaternion deltaRotation = Quaternion::FromAxisAndAngle(_localAngularVelocity, _localAngularVelocity.Length() * (0.5f * delta));
	_rotation = (_rotation * deltaRotation).GetNormalized();

	float mag;
	mag = _rotation.Magnitude();

	if (mag > FLT_EPSILON)
		_rotation /= mag;

	_localVelocity = Quaternion::Rotate(~_rotation, _velocity);

	_angularVelocity = Quaternion::Rotate(_rotation, _localAngularVelocity);

	_speed = _velocity.Length();

	_angularAcceleration = Quaternion::Rotate(_rotation, _localAngularAcceleration);

	Matrix3x3 R, RT;
	R = Quaternion::MakeMatrixFromQuaternion(_rotation);
	RT = R.Transpose();
	_worldInertiaInv = R * _inertiaInv * RT;

	_eularAngle = _rotation.toEulerAngles();
}

void PhysicalObject::UpdateLinearKinematics()
{
	_acceleration = _force / _mass;

	_velocity += _acceleration * P_DELTA;

	_speed = _velocity.Length();

	_linearMomentum = _velocity * _mass;
}

void PhysicalObject::UpdateAngularKinematics()
{
	Vector3 gyroEffect = Vector3::Cross(_localAngularVelocity, (_inertia * _localAngularVelocity));

	_localAngularAcceleration = _inertiaInv * (_momentSum - gyroEffect);

	_localAngularVelocity += _localAngularAcceleration * P_DELTA;

	Quaternion deltaRotation = Quaternion::FromAxisAndAngle(_localAngularVelocity, _localAngularVelocity.Length() * (0.5f * P_DELTA));
	Quaternion tmpRotation = (_rotation * deltaRotation).GetNormalized();

	float mag;
	mag = tmpRotation.Magnitude();

	if (mag > FLT_EPSILON)
		tmpRotation /= mag;

	_localVelocity = Quaternion::Rotate(~tmpRotation, _velocity);

	_angularVelocity = Quaternion::Rotate(tmpRotation, _localAngularVelocity);

	_angularMomentum = _inertia * _angularVelocity;
}

void PhysicalObject::SimulateTransform(shared_ptr<Shape>& shape, float delta) const
{
	if (IsStatic())
		return;

	Vector3 pos = _pos;
	Vector3 eular = _eularAngle;

	if (IsBehaviorFlagSet(LINEAR))
	{
		Vector3 force = _force;
		Vector3 acc = force / _mass;
		Vector3  vel = _velocity + (acc * delta);

		pos += vel * delta;
	}
	if (IsBehaviorFlagSet(ANGULAR))
	{
		Vector3 moment = _momentSum;
		Vector3 gyroEffect = Vector3::Cross(_localAngularVelocity, (_inertia * _localAngularVelocity));

		Vector3 localAngularAcceleration = _inertiaInv * (_momentSum - gyroEffect);

		Vector3 localAngularVelocity = _localAngularVelocity + localAngularAcceleration * delta;

		Quaternion deltaRotation = Quaternion::FromAxisAndAngle(localAngularVelocity, localAngularVelocity.Length() * (0.5f * delta));
		Quaternion rotation = _rotation;
		(rotation * deltaRotation).Normalize();

		float mag;
		mag = rotation.Magnitude();

		if (mag > FLT_EPSILON)
			rotation /= mag;

		eular = rotation.toEulerAngles();
	}

	shape->UpdateTransform(pos, eular);
}

void PhysicalObject::SetShape(Shape* shape)
{
	_shape = shape;
	_inertia = _shape->GetInertiaTensor(_mass);
	_inertiaInv = _inertia.Inverse();
	Matrix3x3 R, RT;
	R = Quaternion::MakeMatrixFromQuaternion(_rotation);
	RT = R.Transpose();
	_worldInertiaInv = R * _inertiaInv * RT;
}

void PhysicalObject::SetRotation(Vector3 eular)
{
	_eularAngle = eular;
	_rotation = XMQuaternionRotationRollPitchYaw(eular.x, eular.y, eular.z);

	Matrix3x3 R, RT;
	R = Quaternion::MakeMatrixFromQuaternion(_rotation);
	RT = R.Transpose();
	_worldInertiaInv = R * _inertiaInv * RT;
}

void PhysicalObject::UpdateVelocityFromMomentum()
{
	if (IsBehaviorFlagSet(LINEAR))
		_velocity = _linearMomentum / _mass;

	if (IsBehaviorFlagSet(ANGULAR))
	{
		_rotation.Normalize();

		Matrix3x3 R, RT;
		R = Quaternion::MakeMatrixFromQuaternion(_rotation);
		RT = R.Transpose();

		_angularVelocity =
			R *
			_worldInertiaInv *
			RT *
			_angularMomentum;

		_localAngularVelocity = Quaternion::Rotate(~_rotation, _angularVelocity);
	}
}

void PhysicalObject::UpdatePosAndRotation()
{
	if (IsBehaviorFlagSet(LINEAR))
	{
		_pos += _velocity * P_DELTA;
	}

	if (IsBehaviorFlagSet(ANGULAR))
	{
		Quaternion deltaRotation = Quaternion::FromAxisAndAngle(_localAngularVelocity, _localAngularVelocity.Length() * (0.5f * P_DELTA));
		_rotation = (_rotation * deltaRotation).GetNormalized();

		float mag;
		mag = _rotation.Magnitude();

		if (mag > FLT_EPSILON)
			_rotation /= mag;

		Matrix3x3 R, RT;
		R = Quaternion::MakeMatrixFromQuaternion(_rotation);
		RT = R.Transpose();

		_worldInertiaInv = R * _inertiaInv * RT;

		_eularAngle = _rotation.toEulerAngles();
	}

	_shape->UpdateTransform(_pos, _eularAngle);
}


void PhysicalObject::ApplyDamping()
{
	if (IsBehaviorFlagSet(LINEAR))
		_velocity *= 0.95f;
	if (IsBehaviorFlagSet(ANGULAR))
	{
		_localAngularVelocity *= 0.95f;
		_localVelocity = Quaternion::Rotate(~_rotation, _velocity);
		_angularVelocity = Quaternion::Rotate(_rotation, _localAngularVelocity);
	}
}

void PhysicalObject::ClampSmallVelocity(Vector3& velocity)
{
	if (fabs(velocity.x) < 0.1f)
		velocity.x = 0;

	if (fabs(velocity.y) < 0.1f)
		velocity.y = 0;

	if (fabs(velocity.z) < 0.1f)
		velocity.z = 0;
}