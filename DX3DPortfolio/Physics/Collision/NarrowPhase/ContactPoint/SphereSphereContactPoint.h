#pragma once
class SphereSphereContactPoint : public ContactPointFinderInterface
{
private:
	// ContactPointFinderInterface��(��) ���� ��ӵ�
	bool DoFindContactPoints(Shape* s1, Shape* s2, CollisionInfo& info) override;
};

