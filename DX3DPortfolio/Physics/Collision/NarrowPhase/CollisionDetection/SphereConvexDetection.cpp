#include "framework.h"
#include "SphereConvexDetection.h"

bool SphereConvexDetection::Detection(Shape* s1, Shape* s2, CollisionInfo& info)
{
    SphereShape* sphere;
    Shape* convex;

    if (s1->GetShapeType() & SPHERE)
    {
        sphere = dynamic_cast<SphereShape*>(s1);
        convex = s2;
    }
    else
    {
        sphere = dynamic_cast<SphereShape*>(s2);
        convex = s1;
    }
     

    if (!sphere || !convex) {
        return false;
    }

    Vector3 sphereCenter = sphere->GetWorldPos();

    Vector3 closestPoint = convex->GetClosestPoint(sphereCenter);

    Vector3 diff = sphereCenter - closestPoint;

    float distance = diff.Length();

    float penetrationDepth = sphere->GetRadius() - distance;

    if (penetrationDepth > 0.0f) 
    {
        info.collisionNormal = diff.GetNormalized();

        info.penetrationDepth = penetrationDepth;

        return true;
    }

    return false;
}
