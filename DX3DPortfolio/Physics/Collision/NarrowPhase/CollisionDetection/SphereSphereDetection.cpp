#include "framework.h"
#include "SphereSphereDetection.h"

bool SphereSphereDetection::Detection(Shape* s1, Shape* s2, CollisionInfo& info)
{
	SphereShape* sphere1 = dynamic_cast<SphereShape*>(s1);
	SphereShape* sphere2 = dynamic_cast<SphereShape*>(s2);

	if (!sphere1 || !sphere2) 
	{
		return false;
	}

	Vector3 len = sphere1->GetWorldPos() - sphere2->GetWorldPos();
	float distance = len.Length();

	float radiusSum = sphere1->GetRadius() + sphere2->GetRadius();

	float penetrationDepth = radiusSum - distance;

	if (penetrationDepth > 0.0f)
	{
		info.collisionNormal = len.GetNormalized();
		info.penetrationDepth = penetrationDepth;
		
		return true;
	}

	return false;
}