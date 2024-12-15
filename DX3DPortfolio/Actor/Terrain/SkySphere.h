#pragma once
#include "Render\State\RasterizerState.h"

class SkySphere : public Actor
{
public:
	SkySphere(float rad, UINT stack, UINT slice, wstring path);
	~SkySphere();

	void Update() override;
	void Render();

	void Debug() override;
private:
	RasterizerState* _rs;
	TextureSphere* _sphere;
};

