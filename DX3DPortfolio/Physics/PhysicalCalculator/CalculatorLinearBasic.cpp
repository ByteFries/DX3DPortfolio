#include "framework.h"
#include "CalculatorLinearBasic.h"

void CalculatorLinearBasic::Calculate(PhysicalObject* target)
{
	Vector3 force{0,0,0};


	Vector3 velocity = target->GetVelocity();

	float speed = velocity.Length();

	if (speed)
	{
		Vector3 resultant = GetLinearAirForce(target, velocity);
		;
		force += resultant;
	}
	
	if (PHYSICS->GetWindSpeed())
	{
		Vector3 resultant = GetLinearWindForce(target, velocity);
	
		force += resultant;
	}

	force.y -= PHYSICS->GetGravity() * target->GetMass();
	target->SetForce(force);

}
