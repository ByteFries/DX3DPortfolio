#include "framework.h"
#include "RigidBody.h"

RigidBody::RigidBody(size_t id, Collider* collider, PhysicalCalculator* calculator)
	:PhysicalObject(id, collider, calculator)
{
	_calculator->SetTarget(this);
}

RigidBody::~RigidBody()
{
}

void RigidBody::UpdateDynamics()
{
	Vector3 acceleration = _force / _mass;

	_velocity += acceleration * DELTA;

	_transform->_translation += _velocity * DELTA;

	float mag;

	_angularVelocity += _inertiaInv * (_momentSum - Vector3::Cross(_angularVelocity, (_inertia * _angularVelocity))) * DELTA;

	_rotation += (_rotation * _angularVelocity) * (0.5f * DELTA);

	mag = _rotation.Magnitude();

	if (mag)
		_rotation /= mag;

	_localVelocity = Quaternion::Rotate(~_rotation, _velocity);

	_speed = _velocity.Length();

	_eularAngle = _rotation.toEulerAngles();
}

void RigidBody::Update()
{
	_calculator->Calculate();

	UpdateDynamics();

	_transform->Update();
	_collider->Update();
}

void RigidBody::AddImpact(Collider::Contact contact)
{
}
