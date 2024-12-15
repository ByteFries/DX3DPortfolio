#include "framework.h"
#include "SphereSphereContactPoint.h"

bool SphereSphereContactPoint::DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info)
{
    SphereShape* sphere;

    if (s1->GetShapeType() & SPHERE)
    {
        sphere = dynamic_cast<SphereShape*>(s1);
    }
    else if (s2->GetShapeType() & SPHERE) 
    {
        sphere = dynamic_cast<SphereShape*>(s2);
    }
    else 
    {
        //std::cerr << "Error: Both shapes are not spheres." << std::endl;
        return false;
    }

    // sphere가 nullptr인지 확인
    if (!sphere) {
        //std::cerr << "Error: Failed to cast to SphereShape." << std::endl;
        return false;
    }
    ContactPoint point;
    point.pos = sphere->GetWorldPos() + info.collisionNormal * (sphere->GetRadius() - info.penetrationDepth);
    point.depth = info.penetrationDepth;
    info.contactPoints.push_back(point);

    return true;
}
