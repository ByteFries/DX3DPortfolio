#pragma once
class Texture
{
private:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Get(wstring file);
	static Texture* Get(wstring key, ID3D11ShaderResourceView* srv);
	static Texture* Load(wstring file);
	static void Delete();

	void PSSetShaderResources(UINT slot);
	void DSSetShaderResources(UINT slot);

	vector<XMFLOAT4> ReadPixels();

	Vector2 GetSize()
	{
		return Vector2(image.GetMetadata().width, image.GetMetadata().height);
	}

	wstring GetPath() { return path; }

	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	ID3D11ShaderResourceView* srv = nullptr;

	ScratchImage image;

	static map<wstring, Texture*> textures;

	wstring path;

	bool isReferred = false;

};

