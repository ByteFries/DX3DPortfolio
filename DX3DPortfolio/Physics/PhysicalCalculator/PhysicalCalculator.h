#pragma once
#include "framework.h"
class PhysicalObject;

class PhysicalCalculator
{
public:
	PhysicalCalculator() { }
	virtual ~PhysicalCalculator() {}

	virtual void Calculate(PhysicalObject* target) abstract;

protected:
	Vector3 GetLinearAirForce(PhysicalObject* target, Vector3 velocity);
	Vector3 GetAngularAirForce(PhysicalObject* target, Vector3 localVelocity);

	Vector3 GetLinearWindForce(PhysicalObject* target, Vector3 relativeVelocity);

};