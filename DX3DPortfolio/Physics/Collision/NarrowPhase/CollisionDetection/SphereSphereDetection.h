#pragma once
class SphereSphereDetection : public CollisionDetectionInterface
{
public:

	// CollisionDetectionInterface을(를) 통해 상속됨
	bool Detection(Shape* s1, Shape* s2, CollisionInfo& info) override;
};

