#include "framework.h"
#include "SphereConvexContactPoint.h"

bool SphereConvexContactPoint::DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info)
{
    SphereShape* sphere;
    Vector3 normal;

    if (s1->GetShapeType() & SPHERE)
    {
        sphere = dynamic_cast<SphereShape*>(s1);
        normal = info.collisionNormal;
    }
    else if (s2->GetShapeType() & SPHERE) 
    {
        sphere = dynamic_cast<SphereShape*>(s2);
        normal = -info.collisionNormal;
    }
    else 
    {
        //std::cerr << "Error: Both shapes are not spheres." << std::endl;
        return false;
    }

    if (!sphere) 
    {
        //std::cerr << "Error: Failed to cast to SphereShape." << std::endl;
        return false;
    }
    ContactPoint point;
    point.pos = sphere->GetWorldPos() + normal * (sphere->GetRadius() - info.penetrationDepth);
    point.depth = info.penetrationDepth;
    info.contactPoints.push_back(point);

    return true;
}
