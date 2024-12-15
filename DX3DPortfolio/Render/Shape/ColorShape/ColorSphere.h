#pragma once
class ColorSphere : public ColorShapeRenderer
{
public:
	ColorSphere(float rad, UINT stack, UINT slice, XMFLOAT4 color);
	~ColorSphere() {}

private:
	void CreateResource() override;

	float _radius;
	UINT _stackCount;
	UINT _sliceCount;
};

