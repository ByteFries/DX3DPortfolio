#pragma once
class Material
{
public:
	Material();
	~Material();

	void SetShader(wstring path);
	void SetVS(wstring path) { _vShader = Shader::AddVS(path); }
	void SetPS(wstring path) { _pShader = Shader::AddPS(path); }
	void IASetBuffer();
	void SetTexture(wstring path);
	void SetDiffuseMap(wstring path);
	//void SetDiffuseMap(Texture* texture);
	void SetSpecularMap(wstring path);
	void SetNormalMap(wstring path);

	void SetName(string name) { _name = name; }
	string GetName() { return _name; }

	MaterialBuffer* GetMatBuffer() { return _mBuffer; }

	void Save(wstring path);
	void Save(string path);
	void Load(wstring path);
	void Load(string path);

private:
	VertexShader* _vShader;
	PixelShader* _pShader;

	Texture* _texture;
	Texture* _diffuseMap;
	Texture* _specularMap;
	Texture* _normalMap;

	MaterialBuffer* _mBuffer;

	string _name;
};

