#pragma once
class TextureCube : public TextureShapeRenderer
{
public:
	TextureCube(Vector3 size, wstring path);
	~TextureCube();

	virtual void SetTexture(wstring path) override;
	void Update() override;
	void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;
private:
	void CreateResource() override;

	vector<TextureQuad*> _surfaces;
	Vector3 _size;
};