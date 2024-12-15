#include "framework.h"
#include "CalculatorAngularBasic.h"

void CalculatorAngularBasic::Calculate(PhysicalObject* target)
{
	Vector3 moments{0,0,0};
	

	Vector3 angularVelocity = target->GetAngularVelocity();
	

	Vector3 tmp = Vector3::Cross(angularVelocity, target->GetPos());

	float localSpeed = tmp.Length();

	if (localSpeed)
	{
		Vector3 linearForce = GetLinearAirForce(target, tmp);

		tmp = Vector3::Cross(target->GetPos(), linearForce);

		moments += tmp;	

		Vector3 angularForce = GetAngularAirForce(target, tmp);

		moments += angularForce;
	}
	
	if (PHYSICS->GetWindSpeed())
	{
		Vector3 windForce = GetLinearWindForce(target, tmp);

		tmp = Vector3::Cross(target->GetPos(), windForce);
		moments += tmp;
	}

	target->SetMomentSum(moments);
}
