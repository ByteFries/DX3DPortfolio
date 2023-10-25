#pragma once
class Material
{
public:
	Material();
	~Material();

	void SetShader(wstring path);
	void SetVS(wstring path);
	void SetPS(wstring path);

	void IASetBuffer();

	void SetTexture(wstring path);
private:
	VertexShader* _vShader;
	PixelShader* _pShader;

	Texture* _texture;

	bool _isTexture = false;
};

