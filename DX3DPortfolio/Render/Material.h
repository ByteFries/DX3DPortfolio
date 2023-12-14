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
	void SetDiffuseMap(wstring path);
	void SetSpecularMap(wstring path);
	void SetNormalMap(wstring path);

	void SetLabel(string name) { _label = name; }
	string GetLabel() { return _label; }

	MaterialBuffer* GetMaterialBuffer() { return _mBuffer; }

	void Save(string path);
	void Load(string path);

	void Debug();
private:
	VertexShader* _vShader;
	PixelShader* _pShader;

	Texture* _texture;
	Texture* _diffuseMap;
	Texture* _specularMap;
	Texture* _normalMap;

	MaterialBuffer* _mBuffer;

	bool _isTexture = false;

	string _label;
};

