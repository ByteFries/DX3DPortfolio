#include "framework.h"
#include "ClippingContactPoint.h"
bool ClippingContactPoint::DoFindContactPoints(Shape* clipper, Shape* target, CollisionInfo& info)
{
	vector<Face> faces = clipper->GetWorldFaces();
	vector<Edge> edges = target->GetWorldEdges();

	for (const Face& face : faces)
	{
		vector<Edge> newEdges;
		
		for (const Edge& edge : edges)
		{
			bool v1Inside = IsPointOnBackside(edge.v1, face) <= 0.001f;
			bool v2Inside = IsPointOnBackside(edge.v2, face) <= 0.001f;
			Vector3 intersect;


			switch ((v1Inside << 1) | v2Inside)
			{
			case 3:
				newEdges.push_back(edge);
				break;

			case 2:
				intersect = LinePlaneIntersect(edge.v1, edge.v2, face);
				newEdges.push_back({edge.v1, intersect});
				break;

			case 1:
				intersect = LinePlaneIntersect(edge.v1, edge.v2, face);
				newEdges.push_back({intersect, edge.v2});
				break;

			case 0: 
				break;
			}
		}

		if (newEdges.size() == 0) return false;

		edges = std::move(newEdges);
	}
	
	//std::unordered_set<Vector3> vertices;
	//
	//for (const Edge& edge : edges) 
	//{
	//	vertices.insert(edge.v1);
	//	vertices.insert(edge.v2);
	//}

	//info.contactPoints.assign(vertices.begin(), vertices.end());

	return true;
}

Vector3 ClippingContactPoint::LinePlaneIntersect(const Vector3& p1, const Vector3& p2, const Face& face)
{
	Vector3 n = face.normal;
	Vector3 lineVec = p2 - p1;

	float denominator = Vector3::Dot(n, lineVec);

	if (abs(denominator) < FLT_EPSILON)
		return p1;

	float t = -Vector3::Dot(n, (p1 - face.edges[0].v1));

	t /= denominator;

	Vector3 intersection = p1 + t * lineVec;

	return intersection;
}

float ClippingContactPoint::IsPointOnBackside(const Vector3& p, const Face& face)
{
	Vector3 n = face.normal;
	Vector3 v = p - face.edges[0].v1;

	return Vector3::Dot(n, v);
}

double ClippingContactPoint::Dot(const Vector3& p1, const Vector3& p2)
{
	double x1 = p1.x;
	double y1 = p1.y;
	double z1 = p1.z;

	double x2 = p2.x;
	double y2 = p2.y;
	double z2 = p2.z;

	return x1 * x2 + y1 * y2 + z1 * z2;
}
