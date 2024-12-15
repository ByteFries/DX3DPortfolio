#pragma once
class SphereConvexContactPoint : public ContactPointFinderInterface
{
public:
private:
	bool DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info) override;
};

