#pragma once
class EdgeFaceContactPoint : public ContactPointFinderInterface
{
public:

private:
	bool DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info) override;
	bool IsPointInFace(const Vector3& point, const Face& face);

};

