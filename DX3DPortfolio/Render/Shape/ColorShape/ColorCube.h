#pragma once
class ColorCube : public ColorShapeRenderer
{
public:
	ColorCube(Vector3 size = { 5.0f,5.0f,5.0f }, XMFLOAT4 color = {1,1,1,1}, RendererInterface* renderer = new PerObjectRenderer);
	~ColorCube();

	void Update() override;
	void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;

	void SetColor(XMFLOAT4 color);

protected:
	void CreateResource() override;

	vector<Transform*> _transforms;
	vector<ColorQuad*> _surfaces;
	Vector3 _size;
};