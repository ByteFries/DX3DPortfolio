#include "framework.h"
#include "SequentialImpulseSolver.h"

SequentialImpulseSolver::SequentialImpulseSolver()
{
}

SequentialImpulseSolver::~SequentialImpulseSolver()
{
}

void SequentialImpulseSolver::Debug()
{
	if (ImGui::TreeNode("ImpulseSetting"))
	{
		ImGui::InputFloat("Slop", &_slop, 0, 0, "%.5f");
		ImGui::InputFloat("BiasFactor", &_biasFactor, 0, 0, "%.10f");
		ImGui::TreePop();
	}
}

void SequentialImpulseSolver::Resolve(vector<PhysicalObject*>& objs, const vector<OverlapPair>& pairs)
{
	if (pairs.size() == 0) return;

	_invDt = 1.f / P_DELTA;

	_cachedJ.clear();
	_cachedJ.resize(ContactPointFinderInterface::GetIndexSize(), {0,0});

	for (int i = 0; i < _solverIterations; i++)
	{
		for (const OverlapPair& pair : pairs)
		{
			PhysicalObject* p1 = objs[pair.index0];
			PhysicalObject* p2 = objs[pair.index1];
			CollisionInfo info = PHYSICS->GetCollisionInfo(pair.index0, pair.index1);
			
			CalculateImpulses(p1, p2, info);
		}
	}
}
/*
void SequentialImpulseSolver::ApplyImpulse(PhysicalObject* p1, PhysicalObject* p2, CollisionInfo& info)
{
		float cachedLJ = info.linearJs[i];
		float cachedAJ = info.angularJs[i];

		info.linearJs[i] = max(linearJ + cachedLJ, 0.0f);
		info.angularJs[i] = max(angularJ + cachedAJ, 0.0f);

		linearJ = info.linearJs[i] - cachedLJ;
		angularJ = info.angularJs[i] - cachedAJ;

		Vector3 linearImpulse = linearJ * info.collisionNormal;
		Vector3 angularImpulse = angularJ * info.collisionNormal;

		lImpulse1 -= linearJ * info.collisionNormal;
		lImpulse2 += linearJ * info.collisionNormal;

		Vector3 relativeVelocity = data.relativeVelocity;

		float vt = Vector3::Dot(relativeVelocity, data.tangent);
		Vector3 lFriction = {};
		Vector3 aFriction = {};
		float coeff = COEFFICIENT::GetKineticFriction(p1->GetMaterial(), p2->GetMaterial());

		float linearFClamp = coeff * info.linearJs[i];
		float angularFClamp = coeff * info.angularJs[i];
		float cachedLF = info.linearF[i];
		float cachedAF = info.angularF[i];
	
		if (fabs(vt) > 0.0)
		{
			float linearF = coeff * angularJ;
			float angularF = coeff * angularJ;

			info.linearF[i] = Utility::Clamp(cachedLF + linearF, -linearFClamp, linearFClamp);
			info.angularF[i] = Utility::Clamp(cachedAF + angularF, -angularFClamp, angularFClamp);
	
			linearF = info.linearF[i] - cachedLF;
			angularF = info.angularF[i] - cachedAF;
	
			Vector3 angularVelocity1 = p1->GetAngularVelocity();
			Vector3 angularVelocity2 = p2->GetAngularVelocity();
			Vector3 relativeAngularVelocity = angularVelocity2 - angularVelocity1;
	
			lFriction = coeff * angularJ * data.tangent;
			aFriction = coeff * data.tangent * relativeAngularVelocity.Length();
			//aFriction = coeff * angularJ * solverData.tangent;
		}
		else
		{
			float linearF = coeff * linearJ;
			float angularF = coeff * angularJ;
	
			info.linearF[i] = Utility::Clamp(cachedLF + linearF, -linearFClamp, linearFClamp);
			info.angularF[i] = Utility::Clamp(cachedAF + angularF, -angularFClamp, angularFClamp);
	
			linearF = info.linearF[i] - cachedLF;
			angularF = info.angularF[i] - cachedAF;
	
			lFriction = coeff * angularJ * data.tangent;
			aFriction = coeff * angularJ * data.tangent;
		}
		
		aImpulse1 -= Vector3::Cross(c_to_1, angularImpulse) * p1->GetWorldInertiaInv();
		aImpulse2 += Vector3::Cross(c_to_2, angularImpulse) * p2->GetWorldInertiaInv();
	}
}
*/
float SequentialImpulseSolver::GetAngularEffect(PhysicalObject* obj, const Vector3& contactVector, const Vector3& collisionNormal) const
{
	Vector3 r = contactVector;
	Vector3 rCrossDir = Vector3::Cross(r, collisionNormal);
	Vector3 angularInertiaEffect = obj->GetWorldInertiaInv() * rCrossDir;
	Vector3 rotationTerm = Vector3::Cross(angularInertiaEffect, r);
	float rotationalComponent = Vector3::Dot(rotationTerm, collisionNormal);

	return rotationalComponent;
}

void SequentialImpulseSolver::CalculateImpulses(PhysicalObject* p1, PhysicalObject* p2, CollisionInfo& info)
{
	vector<ContactPoint> contactPoints = info.contactPoints;

	Vector3 linearImpulse1 = {};
	Vector3 angularImpulse1 = {};
	Vector3 linearImpulse2 = {};
	Vector3 angularImpulse2 = {};
	Data data;

	data.collisionNormal = info.collisionNormal;
	SetMassTerm(p1->GetMass(), p2->GetMass(), data);

	for (int i = 0; i < contactPoints.size(); i++)
	{
		data.contactPoint = contactPoints[i];
		SetRelativeAndTangent(p1, p2, data);
		SetNumerator(p1, p2, data);
		SetDenominator(p1, p2, data);

		///////////////////// impulse /////////////////////

		float j1 = GetJ(p1, data);
		float j2 = GetJ(p2, data);

		int index = data.contactPoint.index;

		float cachedJ1 = _cachedJ[index].first;
		float cachedJ2 = _cachedJ[index].second;

		_cachedJ[index].first = max(j1 + cachedJ1, 0.0f);
		_cachedJ[index].second = max(j2 + cachedJ2, 0.0f);

		j1 = _cachedJ[index].first - cachedJ1;
		j2 = _cachedJ[index].second - cachedJ2;

		Vector3 impulse1 = j1 * info.collisionNormal;
		Vector3 impulse2 = j2 * info.collisionNormal;
		
		///////////////////// friction /////////////////////

		float tangentSpeed = Vector3::Dot(data.relativeVelocity, data.tangent);

		float coeff = 0;
		Vector3 friction1;
		Vector3 friction2;

		if (tangentSpeed > 0.1f)
		{
			coeff = COEFFICIENT::GetKineticFriction(p1->GetMaterial(), p2->GetMaterial());

			friction1 = coeff * j1 * data.tangent;
			friction2 = coeff * j2 * data.tangent;
		}
		else
		{
			coeff = COEFFICIENT::GetStaticFriction(p1->GetMaterial(), p2->GetMaterial());

			friction1 = min(coeff * j1, tangentSpeed) * data.tangent;
			friction2 = min(coeff * j2, tangentSpeed) * data.tangent;
		}

		linearImpulse1 += impulse1 - friction1;
		linearImpulse2 += impulse2 - friction2;


		angularImpulse1 += Vector3::Cross(data.contactPoint.pos, (impulse1 - friction1)) * p1->GetWorldInertiaInv();
		angularImpulse2 += Vector3::Cross(data.contactPoint.pos, (impulse2 - friction2)) * p2->GetWorldInertiaInv();
	}

	AddImpulse(p1, -linearImpulse1, -angularImpulse1);
	AddImpulse(p2, linearImpulse2, angularImpulse2);
}

void SequentialImpulseSolver::SetRelativeAndTangent(PhysicalObject* p1, PhysicalObject* p2, Data& data)
{
	Vector3 p1_velocity = p1->GetVelocity() + Vector3::Cross(p1->GetAngularVelocity(), data.contactPoint.c_to_1);
	Vector3 p2_velocity = p2->GetVelocity() + Vector3::Cross(p2->GetAngularVelocity(), data.contactPoint.c_to_2);

	data.relativeVelocity = p2_velocity - p1_velocity;

	Vector3 frictionDir = data.relativeVelocity - Vector3::Dot(data.relativeVelocity, data.collisionNormal) * data.collisionNormal;
	data.tangent = frictionDir.GetNormalized();
}

void SequentialImpulseSolver::SetNumerator(PhysicalObject* p1, PhysicalObject* p2, Data& data)
{
	float e = COEFFICIENT::GetRestitution(p1->GetMaterial(), p2->GetMaterial());

	float directionRelativeVelocity = Vector3::Dot(data.relativeVelocity, data.collisionNormal);

	float bias = _biasFactor * _invDt * max(0.0f, data.contactPoint.depth - _slop);

	float impulseNumerator = -(1 + e) * directionRelativeVelocity + bias;

	data.numerator = impulseNumerator;
}

void SequentialImpulseSolver::SetDenominator(PhysicalObject* p1, PhysicalObject* p2, Data& data)
{
	float angularEffect1 = GetAngularEffect(p1, data.contactPoint.c_to_1, data.collisionNormal);
	float angularEffect2 = GetAngularEffect(p2, data.contactPoint.c_to_2, data.collisionNormal);

	data.denominator = data.massTerm + angularEffect1 + angularEffect2;
}

void SequentialImpulseSolver::SetMassTerm(float mass1, float mass2, Data& data)
{
	float massTerm = 0;

	if (mass1 == 0)
	{
		massTerm = 1.0f / mass2;
	}
	else if (mass2 == 0)
	{
		massTerm = 1.0f / mass1;
	}
	else
	{
		massTerm = 1.0f / mass1 + 1.0f / mass2;
	}

	data.massTerm = massTerm;
}

float SequentialImpulseSolver::GetJ(PhysicalObject* obj, Data& data)
{
	bool hasLinear = obj->IsBehaviorFlagSet(LINEAR);
	bool hasAngular = obj->IsBehaviorFlagSet(ANGULAR);

	float j = 0;

	if (hasAngular)
	{
		j = data.numerator / data.denominator;
	}
	else if (hasLinear)
	{
		j = data.numerator / data.massTerm;
	}

	return j;
}

void SequentialImpulseSolver::AddImpulse(PhysicalObject* obj, const Vector3& linearImpulse, const Vector3& angularImpulse)
{
	bool hasLinear = obj->IsBehaviorFlagSet(LINEAR);
	bool hasAngular = obj->IsBehaviorFlagSet(ANGULAR);

	if (hasLinear)
	{
		Vector3 impulse = linearImpulse / obj->GetMass();
		Vector3 velocity = obj->GetVelocity() + impulse;

		obj->SetVelocity(velocity);
	}
	if (hasAngular)
	{
		Vector3 angularVelocity = obj->GetAngularVelocity() + angularImpulse;
		Vector3 localAngularVelocity = Quaternion::Rotate(~obj->GetRotation(), angularVelocity);

		obj->SetAngularVelocity(angularVelocity);
		obj->SetLocalAngularVelocity(localAngularVelocity);
	}
}