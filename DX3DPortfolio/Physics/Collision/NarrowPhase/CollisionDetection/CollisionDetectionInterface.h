#pragma once


struct CollisionInfo
{
	vector<class ContactPoint> contactPoints;
	Vector3 collisionNormal;
	float penetrationDepth;
};


class CollisionDetectionInterface
{
public:
	virtual bool Detection(Shape* s1, Shape* s2, CollisionInfo& info) abstract;
protected:
};

