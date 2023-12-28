#include "framework.h"
#include "Texture.h"

unordered_map<wstring, Texture*> Texture::_textures = {};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:_srv(srv), _image(move(image))
{
}

Texture::~Texture()
{
	_srv->Release();
}

Texture* Texture::Get(wstring file)
{
	wstring path = file;
	
	if (file == L"")
		return nullptr;

	if (_textures.count(file) > 0)
		return _textures[file];

	ScratchImage img;

	LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, img);

	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView
	(
		DEVICE,
		img.GetImages(),
		img.GetImageCount(),
		img.GetMetadata(),
		&srv
	);

	_textures[file] = new Texture(srv, img);
	_textures[file]->_path = path;

	return _textures[file];
}

Texture* Texture::Get(wstring key, ID3D11ShaderResourceView* srv)
{
	ScratchImage img;

	_textures[key] = new Texture(srv, img);
	_textures[key]->_path = key;

	return _textures[key];
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : _textures)
		delete pair.second;

	_textures.clear();
}

void Texture::PSSetShaderResource(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &_srv);
}

XMFLOAT2 Texture::GetSize()
{
	return XMFLOAT2(_image.GetMetadata().width, _image.GetMetadata().height);
}

vector<XMFLOAT4> Texture::ReadPixels()
{
	unsigned char* pixels = _image.GetPixels();

	UINT size = _image.GetPixelsSize() * 0.25f;

	vector<XMFLOAT4> colors(size);

	float scale = 1.0f / 255.0f;

	UINT count = 0;

	for (XMFLOAT4& color : colors)
	{
		color.x = pixels[count++] * scale;
		color.y = pixels[count++] * scale;
		color.z = pixels[count++] * scale;
		color.w = pixels[count++] * scale;
	}

	return colors;
}