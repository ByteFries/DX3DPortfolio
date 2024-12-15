#include "framework.h"
#include "ContactPointFinderInterface.h"
UINT ContactPointFinderInterface::indexCounter = 0;

bool ContactPointFinderInterface::FindContactPoint(Shape* s1, Shape* s2, CollisionInfo& info)
{
	if (DoFindContactPoints(s1, s2, info))
	{
		InitializePoints(s1, s2, info);
		return true;
	}
	return false;
}

void ContactPointFinderInterface::InitializePoints(Shape* s1, Shape* s2, CollisionInfo& info)
{
	vector<ContactPoint>& points = info.contactPoints;

	for (ContactPoint&  point : points)
	{
		point.index = indexCounter++;
		point.c_to_1 = s1->GetWorldPos() - point.pos;
		point.c_to_2 = s2->GetWorldPos() - point.pos;
	}

}
