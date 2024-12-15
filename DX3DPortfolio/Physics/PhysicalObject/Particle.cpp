#include "framework.h"
#include "Particle.h"

Particle::Particle(size_t id, Collider* collider, PhysicalCalculator* calculator)
	:PhysicalObject(id, collider, calculator)
{
	_calculator->SetTarget(this);
}

Particle::~Particle()
{
}

void Particle::Update()
{
	float dt = DELTA;

	_calculator->Calculate();

	Vector3 acceleration = _force / _mass;

	Vector3 dv = acceleration * dt;
	_velocity += dv;
	
	Vector3 ds = _velocity * dt;
	_pos += ds;
	
	_speed = _velocity.Length();

	_transform->Update();
	_collider->Update();
}

void Particle::AddImpact(Collider::Contact contact)
{
}
