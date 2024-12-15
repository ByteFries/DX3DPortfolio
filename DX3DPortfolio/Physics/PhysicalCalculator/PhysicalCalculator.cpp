#include "framework.h"

Vector3 PhysicalCalculator::GetLinearAirForce(PhysicalObject* target, Vector3 velocity)
{
    Vector3 dragDir = -velocity.GetNormalized();

	if (dragDir == Vector3( 0,0,0 ))
		return Vector3(0,0,0);

    float speed = velocity.Length();
	float airDensity = PHYSICS->GetAirDen();
	float linearCoefficient = COEFFICIENT::GetLinearDrag();
	float frontalArea = target->GetShape()->GetFrontalArea(dragDir);

	float dragForceMag = 0.5f * airDensity * speed * speed * linearCoefficient * frontalArea;

    return dragDir * dragForceMag;
}

Vector3 PhysicalCalculator::GetAngularAirForce(PhysicalObject* target, Vector3 localVelocity)
{
	Shape* shape = target->GetShape();
	float surfaceArea = shape->GetSurfaceArea();

	float localSpeed = localVelocity.Length();
	Vector3 dragDir = -localVelocity.GetNormalized();

	float angularCoefficient = (localSpeed == 0) ?
		COEFFICIENT::GetDragCoefficient(shape->GetShapeType(), false) :
		COEFFICIENT::GetDragCoefficient(shape->GetShapeType(), true);

	float airDensity = PHYSICS->GetAirDen();
	float dragForceMag = airDensity * angularCoefficient * surfaceArea * localSpeed * localSpeed;

	//return dragDir * dragForceMag;

	return -localVelocity * angularCoefficient;
}

Vector3 PhysicalCalculator::GetLinearWindForce(PhysicalObject* target, Vector3 relativeVelocity) // 바람과 타겟의 상대 속도
{
    float speed = relativeVelocity.Length();
	
	float airDensity = PHYSICS->GetAirDen();
	float linearCoefficient = COEFFICIENT::GetLinearDrag();
	float frontalArea = target->GetShape()->GetFrontalArea(PHYSICS->GetWindDirection());

	float windForceMag = 0.5f * airDensity * speed * speed * linearCoefficient * frontalArea;

    return  relativeVelocity * windForceMag;
}


