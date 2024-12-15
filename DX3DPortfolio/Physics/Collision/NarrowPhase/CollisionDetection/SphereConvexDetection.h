#pragma once
class SphereConvexDetection : public CollisionDetectionInterface
{
public:

	bool Detection(Shape* s1, Shape* s2, CollisionInfo& info) override;
};

