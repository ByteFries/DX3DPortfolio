#pragma once
class SphereSphereDetection : public CollisionDetectionInterface
{
public:

	// CollisionDetectionInterface��(��) ���� ��ӵ�
	bool Detection(Shape* s1, Shape* s2, CollisionInfo& info) override;
};

