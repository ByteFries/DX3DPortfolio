#pragma once
class ClippingContactPoint : public ContactPointFinderInterface
{
private:
	bool DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info) override;

	vector<Vector3> ClipPoligonAgainstPlane(const Face& aFace, const Vector3& facePoint, const Vector3& normal);
	Vector3 LinePlaneIntersect(const Vector3& p1, const Vector3& p2, const Face& face);
	float IsPointOnBackside(const Vector3& p, const Face& face);

	double Dot(const Vector3& p1, const Vector3& p2);

};

