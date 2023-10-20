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

private:
	VertexShader* _vShader;
	PixelShader* _pShader;

	
};

