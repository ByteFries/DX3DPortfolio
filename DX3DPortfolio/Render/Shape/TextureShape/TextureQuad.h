#pragma once
class TextureQuad : public TextureShapeRenderer
{
public:
	TextureQuad(Vector2 size, RendererInterface* renderer = new PerObjectRenderer);
	TextureQuad(Vector2 size, wstring path, RendererInterface* renderer = new PerObjectRenderer);
	virtual ~TextureQuad();

	void SetTexture(wstring path);
protected:
	void CreateResource() override;

	Vector2 _size;
};

