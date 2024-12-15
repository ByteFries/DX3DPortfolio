#pragma once
class CapsuleShape : public Shape
{
public:
	CapsuleShape(float height, float radius, int stack, int slice);
	~CapsuleShape() {}
	std::shared_ptr<Shape> GetClone() override;

	float GetFrontalArea(Vector3 direction) override;

	Matrix3x3 GetInertiaTensor(float mass) override;
private:
	void CreateResource() override;
	void CreateFaces() override;

	float _height;
	float _radius;
	int _stackCount;
	int _sliceCount;
};

