#pragma once
class ColorQuad :public ColorShapeRenderer
{
public:
	ColorQuad(Vector2 size, XMFLOAT4 color = {1,1,1,1}, RendererInterface* renderer = new PerObjectRenderer);
	
	~ColorQuad();

	virtual void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;
	void SetColor(XMFLOAT4 color);

private:
	virtual void CreateResource() override;

	Vector2 _size;
};

