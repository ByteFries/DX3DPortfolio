#pragma once
class PlatformBase : public Actor
{
public:
	PlatformBase();
	virtual ~PlatformBase();

	void SetTexture(wstring path);

	virtual void Update();
	virtual void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
protected:
	virtual void Init() abstract;

	PhysicalObject* _rigidBody;
	TextureShapeRenderer* _render;
};