#pragma once
class TextureSphere : public TextureShapeRenderer
{
public:
	TextureSphere(float rad, UINT stack, UINT slice, RendererInterface* renderer = new PerObjectRenderer);
	TextureSphere(float rad, UINT stack, UINT slice, wstring path, RendererInterface* renderer = new PerObjectRenderer);
	~TextureSphere() {}

	void SetTexture(wstring path) override;

private:
	void CreateResource() override;

	float _radius;
	UINT _stackCount;
	UINT _sliceCount;
};

