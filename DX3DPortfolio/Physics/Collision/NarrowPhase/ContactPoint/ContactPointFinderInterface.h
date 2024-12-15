#pragma once

using namespace ShapeNamespace;

struct ContactPoint
{
	int index = -1;
	float depth = 0;
	Vector3 pos = {};

	Vector3 c_to_1 = {};
	Vector3 c_to_2 = {};
};

class ContactPointFinderInterface
{
public:
	bool FindContactPoint(Shape* s1, Shape* s2, CollisionInfo& info);
	static UINT GetIndexSize() { return indexCounter; }
	static void ResetCounter() { indexCounter = 0; }
protected:
	static UINT indexCounter;

	virtual bool DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info) abstract;
	void InitializePoints(Shape* s1, Shape* s2, CollisionInfo& info);
};

