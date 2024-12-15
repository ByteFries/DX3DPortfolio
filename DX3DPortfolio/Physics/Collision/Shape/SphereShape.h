#pragma once
class SphereShape : public Shape
{
public:
	SphereShape(float radius, UINT stack, UINT slice);
	std::shared_ptr<Shape> GetClone() override;

	float GetFrontalArea(Vector3 direction) override;

	Matrix3x3 GetInertiaTensor(float mass) override;

	Vector3 GetPos() { return _transform->_translation; }
	virtual Vector3 FindFurthestPoint(const Vector3& direction) override;
	float GetRadius() { return _radius; }
private:
	void CreateResource() override;
	void CreateFaces() override;
	float _radius;
	UINT _stackCount;
	UINT _sliceCount;
};

