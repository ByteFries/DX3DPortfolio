#include "framework.h"
#include "EdgeFaceContactPoint.h"

bool EdgeFaceContactPoint::DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info)
{
    vector<Face> faces = s1->GetWorldFaces();
    vector<Edge> edges = s2->GetWorldEdges();
    map<Vector3, float> pointsAndDepths;
    Vector3 collisionNormal = info.collisionNormal;

    for (const Face& face : faces)
    {
        Vector3 faceNormal = face.normal;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
        Vector3 faceVertex = face.edges[0].v1;

        for (const Edge& edge : edges)
        {
            Vector3 edgeVector = edge.v2 - edge.v1;
            float dotProduct = Vector3::Dot(edgeVector, faceNormal);

            if (fabs(dotProduct) == 0.0f)
                continue;

            float t = Vector3::Dot(faceNormal, (faceVertex - edge.v1)) / dotProduct;

            if (t >= 0 && t <= 1)
            {
                Vector3 contactPoint = edge.v1 + t * edgeVector;

                if (IsPointInFace(contactPoint, face))
                {
                    // 엣지 시작점과 접촉점 방향 비교
                    Vector3 edgeDirection = (edge.v1 - contactPoint).GetNormalized();
                    float edgeDotNormal = Vector3::Dot(edgeDirection, collisionNormal);
                    // 만약 collisionNormal 방향과 반대라면, edge2가 침투한 상황
                    if (edgeDotNormal < 0)
                    {
                        pointsAndDepths[contactPoint] = abs(Vector3::Dot(contactPoint - edge.v2, -collisionNormal));
                    }
                    else
                        pointsAndDepths[contactPoint] = abs(Vector3::Dot(contactPoint - edge.v1, -collisionNormal));
                }
            }
        }
    }

    if (pointsAndDepths.size() == 0)
        return false;

    for (const pair<Vector3, float>& p : pointsAndDepths)
    {
        ContactPoint point;
        point.pos = p.first;
        point.depth = p.second;
        info.contactPoints.push_back(point);
    }

    return true;
}

bool EdgeFaceContactPoint::IsPointInFace(const Vector3& point, const Face& face)
{
    Vector3 normal = face.normal;

    float distance = Vector3::Dot(normal, (point - face.edges[0].v1));
    if (fabs(distance) > FLT_EPSILON)
        return false;

    for (size_t i = 0; i < face.edges.size(); ++i)
    {
        Vector3 edgeVector = face.edges[i].v2 - face.edges[i].v1;
        Vector3 pointVector = point - face.edges[i].v1;

        if (Vector3::Dot(normal, Vector3::Cross(edgeVector, pointVector)) < 0)
            return false;
    }

    return true;
}
