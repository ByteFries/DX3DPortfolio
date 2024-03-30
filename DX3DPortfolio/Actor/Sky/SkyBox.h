#pragma once
class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	void Update();

	void Render();
	void Debug();

private:
	RasterizerState* _rs;

	Sphere* _sphere;

	SkyBuffer* _sBuffer;
};