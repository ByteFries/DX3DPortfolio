#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::textures = {};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:srv(srv), image(move(image))
{
}

Texture::~Texture()
{
	if (!isReferred)
		srv->Release();
}

Texture* Texture::Get(wstring file)
{
	wstring path = file;

	if (file == L"")
		return nullptr;

	assert(PathFileExists(file.c_str()));

	if (textures.count(file) > 0)
		return textures[file];

	ScratchImage image;

	wstring extension = Utility::GetExtension(file);

	if (extension == L"tga" || extension == L"TGA")
		LoadFromTGAFile(file.c_str(), nullptr, image);
	else if (extension == L"dds" || extension == L"DDS")
		LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
	else
		LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	textures[file] = new Texture(srv, image);
	textures[file]->path = path;

	return textures[file];
}

Texture* Texture::Get(wstring key, ID3D11ShaderResourceView* srv)
{
	if (textures.count(key) > 0)
		return textures[key];

	ScratchImage image;

	textures.emplace(key, new Texture(srv, image));
	textures[key]->isReferred = true;

	return textures[key];
}

Texture* Texture::Load(wstring file)
{
	wstring path = file;

	if (file == L"")
		return nullptr;

	file = L"_Texture/" + file;

	//assert(PathFileExists(file.c_str()));

	if (textures.count(file) > 0)
		textures.erase(file);

	ScratchImage image;

	wstring extension = Utility::GetExtension(file);

	if (extension == L"tga" || extension == L"TGA")
		LoadFromTGAFile(file.c_str(), nullptr, image);
	else if (extension == L"dds" || extension == L"DDS")
		LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
	else
		LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	textures[file] = new Texture(srv, image);
	textures[file]->path = path;

	return textures[file];
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : textures)
		delete pair.second;

	textures.clear();
}

void Texture::PSSetShaderResources(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &srv);
}

void Texture::DSSetShaderResources(UINT slot)
{
	DC->DSSetShaderResources(slot, 1, &srv);
}

vector<XMFLOAT4> Texture::ReadPixels()
{
	unsigned char* pixels = image.GetPixels();

	UINT size = image.GetPixelsSize() * 0.25f; // / 4

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
