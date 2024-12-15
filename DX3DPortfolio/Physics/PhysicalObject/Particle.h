#pragma once
class Particle : public PhysicalObject
{
	friend class PhysicsManager;

	Particle(size_t id, Collider* collider, PhysicalCalculator* calculator);
	virtual ~Particle();

	void AddImpact(Collider::Contact contact) override;
public:
	void Update() override;
};