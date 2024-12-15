#include "framework.h"
#include "CalculatorLABasic.h"

void CalculatorLABasic::Calculate(PhysicalObject* target)
{
	Vector3 force{ 0,0,0 };
	Vector3 moments{ 0,0,0 };

	Vector3 targetPos = target->GetPos();
	Vector3 localVelocity = target->GetLocalVelocity();
	Vector3 localAngularVelocity = target->GetLocalAngularVelocity();

	//Vector3 linearForce = GetLinearAirForce(target, localVelocity);
	//force += linearForce;
	//moments += GetAngularAirForce(target, localAngularVelocity);

	
	//if (PHYSICS->GetWindSpeed())
	//{
	//	Vector3 windForce = GetLinearWindForce(target, localVel);
	//	force += windForce;
	//	//tmp = Vector3::Cross(targetPos, windForce);
	//	//moments += tmp;
	//}

	force = Quaternion::Rotate(target->GetRotation(), force); 
	force.y -= GRAVITY * target->GetMass();
	target->SetMomentSum(moments);
	
	target->SetForce(force);
}