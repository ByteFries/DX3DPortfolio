#pragma once

using namespace PhysicsType;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	bool CheckCollsion(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info);
	void ResolveCollisionOverlap(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info);

private:
	bool HandleCollision(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info, CollisionDetectionInterface* collisionDetector, ContactPointFinderInterface* contactFinder);
	void FindCollisionTime(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info, CollisionDetectionInterface* collisionDetector, ContactPointFinderInterface* contactFinder);
	
	const int _shapeCombinationToIndex[7] = {-1, 0, 1, 2, 3, 4, 5 };

	vector<CollisionDetectionInterface*> _collisionDetectors;
	vector<ContactPointFinderInterface*> _contactPointFinders;
};