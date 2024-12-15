#pragma once
using namespace PhysicsType;

class SequentialImpulseSolver
{
public:
	SequentialImpulseSolver();
	~SequentialImpulseSolver();

	void Resolve(vector<PhysicalObject*>& objs, const vector<OverlapPair>& pairs);

	void Debug();
private:
	struct Data
	{
		Vector3 collisionNormal;
		ContactPoint contactPoint;
		Vector3 relativeVelocity;
		Vector3 tangent;
		float massTerm;
		float denominator;
		float numerator;
	};

	void SetRelativeAndTangent(PhysicalObject* p1, PhysicalObject* p2, Data& data);
	void SetNumerator(PhysicalObject* p1, PhysicalObject* p2, Data& data);
	void SetDenominator(PhysicalObject* p1, PhysicalObject* p2, Data& data);
	void SetMassTerm(float mass1, float mass2, Data& data);
	
	float GetAngularEffect(PhysicalObject* obj, const Vector3& contactVector, const Vector3& collisionNormal) const;
	float GetJ(PhysicalObject* obj, Data& data);

	void AddImpulse(PhysicalObject* obj, const Vector3& linearImpulse, const Vector3& angularImpulse);
	void CalculateImpulses(PhysicalObject* p1, PhysicalObject* p2, CollisionInfo& info);
	
	UINT _solverIterations = 5;
	float _slop = 0.01f;
	float _biasFactor = 0.000000f;
	float _invDt;

	vector<pair<float, float>> _cachedJ;
};