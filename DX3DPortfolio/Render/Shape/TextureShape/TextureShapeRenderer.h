#pragma once
class TextureShapeRenderer : public MeshRO
{
public:
	TextureShapeRenderer(RendererInterface* renderer = new PerObjectRenderer);
	TextureShapeRenderer(wstring path, RendererInterface* renderer = new PerObjectRenderer);

	virtual ~TextureShapeRenderer() {}
	virtual void SetTexture(wstring path) abstract;

protected:
	std::array<pair<wstring, wstring>, 2> GetShaderNames() const override;
};