#pragma once
class Texture
{
private:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Get(wstring file);
	static Texture* Get(wstring key, ID3D11ShaderResourceView* srv);
	static void Delete();

	wstring GetPath() { return _path; }

	void PSSetShaderResource(UINT slot);

	XMFLOAT2 GetSize();

	vector<XMFLOAT4> ReadPixels();

private:
	ID3D11ShaderResourceView* _srv = nullptr;
	ScratchImage _image;

	static unordered_map<wstring, Texture*> _textures;

	wstring _path;

	bool _isRef = false;
};

