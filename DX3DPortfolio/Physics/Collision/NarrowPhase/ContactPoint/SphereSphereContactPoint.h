#pragma once
class SphereSphereContactPoint : public ContactPointFinderInterface
{
private:
	// ContactPointFinderInterface을(를) 통해 상속됨
	bool DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info) override;
};

