#include "framework.h"
#include "TextureCube.h"

TextureCube::TextureCube(Vector3 size, wstring path)
	:_size(size)
{
	CreateResource();
	SetTexture(path);
}

TextureCube::~TextureCube()
{
	for (TextureQuad* quad : _surfaces)
		delete quad;
}

void TextureCube::SetTexture(wstring path)
{
	for (TextureQuad* quad : _surfaces)	
		quad->SetTexture(path);
}

void TextureCube::Update()
{
	_transform->Update();

	for (TextureQuad* quad : _surfaces)
		quad->Update();
}

void TextureCube::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	for (TextureQuad* quad : _surfaces)
	{
		quad->Render(type);
	}
}

void TextureCube::CreateResource()
{
	//F
	{
		TextureQuad* quad = new TextureQuad(Vector2(_size.x, _size.y));
		quad->GetTransform()->_translation.z += _size.z * 0.5f;
		quad->GetTransform()->_rotation.x += 3.141592f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//B
	{
		TextureQuad* quad = new TextureQuad(Vector2(_size.x, _size.y));
		quad->GetTransform()->_translation.z -= _size.z * 0.5f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//T
	{
		TextureQuad* quad = new TextureQuad(Vector2(_size.x, _size.z));
		quad->GetTransform()->_translation.y += _size.y * 0.5f;
		quad->GetTransform()->_rotation.x += 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//D
	{
		TextureQuad* quad = new TextureQuad(Vector2(_size.x, _size.z));
		quad->GetTransform()->_translation.y -= _size.y * 0.5f;
		quad->GetTransform()->_rotation.x -= 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//L
	{
		TextureQuad* quad = new TextureQuad(Vector2(_size.z, _size.y));
		quad->GetTransform()->_translation.x -= _size.x * 0.5f;
		quad->GetTransform()->_rotation.y = 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//R
	{
		TextureQuad* quad = new TextureQuad(Vector2(_size.z, _size.y));
		quad->GetTransform()->_translation.x += _size.x * 0.5f;
		quad->GetTransform()->_rotation.y -= 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}
}
