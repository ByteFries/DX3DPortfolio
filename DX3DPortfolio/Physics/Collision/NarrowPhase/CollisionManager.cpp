#include "framework.h"
#include "CollisionManager.h"

using namespace ShapeNamespace;

CollisionManager::CollisionManager()
{
    _collisionDetectors.resize(COMBINATION_COUNT);
    _collisionDetectors[_shapeCombinationToIndex[SPHERE_SPHERE]] = new SphereSphereDetection();
    _collisionDetectors[_shapeCombinationToIndex[SPHERE_BOX]] = new GJK_EPA();
    //_collisionDetectors[_shapeCombinationToIndex[SPHERE_CAPSULE]] = new SphereConvexDetection();
    _collisionDetectors[_shapeCombinationToIndex[SPHERE_CAPSULE]] = new GJK_EPA();
    _collisionDetectors[_shapeCombinationToIndex[BOX_BOX]] = new GJK_EPA();
    _collisionDetectors[_shapeCombinationToIndex[BOX_CAPSULE]] = new GJK_EPA();
    _collisionDetectors[_shapeCombinationToIndex[CAPSULE_CAPSULE]] = new GJK_EPA();

    _contactPointFinders.resize(COMBINATION_COUNT);
    _contactPointFinders[_shapeCombinationToIndex[SPHERE_SPHERE]] = new SphereSphereContactPoint();
    _contactPointFinders[_shapeCombinationToIndex[SPHERE_BOX]] = new SphereConvexContactPoint();
    _contactPointFinders[_shapeCombinationToIndex[SPHERE_CAPSULE]] = new SphereConvexContactPoint();
    _contactPointFinders[_shapeCombinationToIndex[BOX_BOX]] = new EdgeFaceContactPoint();
    _contactPointFinders[_shapeCombinationToIndex[BOX_CAPSULE]] = new EdgeFaceContactPoint();
    _contactPointFinders[_shapeCombinationToIndex[CAPSULE_CAPSULE]] = new EdgeFaceContactPoint();
}

CollisionManager::~CollisionManager()
{
    for (auto detector : _collisionDetectors)
        delete detector;

    _collisionDetectors.clear();

    for (auto finder : _contactPointFinders)
        delete finder;

    _contactPointFinders.clear();
}

bool CollisionManager::CheckCollsion(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info)
{
    Shape* s1 = o1->GetShape();
    Shape* s2 = o2->GetShape();

    int combinedCollisionType = s1->GetShapeType() | s2->GetShapeType();

    if (combinedCollisionType < 0 || combinedCollisionType >= COMBINATION_COUNT)
    {
        // 오류 처리
        return false;
    }

    int index = _shapeCombinationToIndex[combinedCollisionType];
    
    if (index < 0 || index >= COMBINATION_COUNT) {
        // 오류 처리
        return false;
    }

    return HandleCollision(o1, o2, info, _collisionDetectors[index], _contactPointFinders[index]);
}

bool CollisionManager::HandleCollision(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info, CollisionDetectionInterface* collisionDetector, ContactPointFinderInterface* contactFinder)
{
    Shape* s1 = o1->GetShape();
    Shape* s2 = o2->GetShape();

    bool collisionAtZero = collisionDetector->Detection(s1, s2, info);

    if (!collisionAtZero)
    {
        return false;
    }

    bool requiresBlocking = (o1->IsBlocking() && o2->IsBlocking()) != 0;

    if (requiresBlocking)
    {
        if (!contactFinder->FindContactPoint(s1, s2, info))
            contactFinder->FindContactPoint(s2, s1, info); //디버거 처리 필요
    }

    return true;
}

void CollisionManager::FindCollisionTime(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info, CollisionDetectionInterface* collisionDetector, ContactPointFinderInterface* contactFinder)
{
    /*
    shared_ptr<Shape> s1 = o1->GetShape()->GetClone();
    shared_ptr<Shape> s2 = o2->GetShape()->GetClone();

    float startTime = 0.0f;
    float endTime = P_DELTA;
    float midTime;

    while (endTime - startTime > FLT_EPSILON)
    {
        midTime = (endTime + startTime) * 0.5;

        o1->SimulateTransform(s1, midTime);
        o2->SimulateTransform(s2, midTime);

        if (collisionDetector->Detection(s1, s2, info))
            endTime = midTime;
        else
            startTime = midTime;
    }

    float delta = (startTime + endTime) * 0.5f;

    o1->SimulateTransform(s1, delta);
    o2->SimulateTransform(s2, delta);

    if (!collisionDetector->Detection(s1, s2, info))
    {
        delta = endTime;
        o1->SimulateTransform(s1, delta);
        o2->SimulateTransform(s2, delta);
    }

    //o1->SetCollisionTime(delta);
    //o2->SetCollisionTime(delta);

    if (isnan(info.collisionNormal.x))
        collisionDetector->Detection(s1, s2, info);

    if (!contactFinder->FindContactPoint(s1, s2, info))
    {
        if (!contactFinder->FindContactPoint(s2, s1, info))
        {
            //디버거 처리 필요
        }
    }
    */
}

void CollisionManager::ResolveCollisionOverlap(PhysicalObject* o1, PhysicalObject* o2, CollisionInfo& info)
{
    Vector3 overlap;

    int behaviorFlag1 = o1->GetBehaviorFlag();
    int behaviorFlag2 = o2->GetBehaviorFlag();

    if (behaviorFlag1 == STATIC)
    {
        overlap = info.collisionNormal * info.penetrationDepth;

        Vector3 newPosition = o2->GetPos() - overlap;
        o2->SetPos(newPosition);
    }
    else if (behaviorFlag2 == STATIC)
    {
        overlap = info.collisionNormal * info.penetrationDepth;

        Vector3 newPosition = o1->GetPos() + overlap;
        o1->SetPos(newPosition);
    }
    else
    {
        overlap = info.collisionNormal * info.penetrationDepth;

        if (isnan(overlap.x))
            overlap = {};

        Vector3 newPositionA = o1->GetPos() + (overlap * (o2->GetMass() / (o1->GetMass() + o2->GetMass())));
        Vector3 newPositionB = o2->GetPos() - (overlap * (o1->GetMass() / (o1->GetMass() + o2->GetMass())));

        o1->SetPos(newPositionA);
        o2->SetPos(newPositionB);
    }
}