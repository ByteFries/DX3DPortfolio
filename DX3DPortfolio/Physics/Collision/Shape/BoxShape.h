#pragma once
class BoxShape : public Shape
{
public:
	BoxShape(Vector3 size);
	~BoxShape() {}
	std::shared_ptr<Shape> GetClone() override;

	float GetFrontalArea(Vector3 direction) override;
	
	Matrix3x3 GetInertiaTensor(float mass) override;
private:
	void CreateResource() override;
	void CreateFaces() override;
	
	float ProjectArea(float width, float height, float nx, float ny, float nz, Vector3 direction);

	Vector3 _size;

};

