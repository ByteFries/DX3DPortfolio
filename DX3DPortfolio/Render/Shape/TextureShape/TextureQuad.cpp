#include "framework.h"
#include "TextureQuad.h"

TextureQuad::TextureQuad(Vector2 size, RendererInterface* renderer)
	:TextureShapeRenderer(renderer), _size(size)
{
	CreateResource();
}

TextureQuad::TextureQuad(Vector2 size, wstring path, RendererInterface* renderer)
	:TextureShapeRenderer(path,renderer), _size(size)
{
	CreateResource();
}

TextureQuad::~TextureQuad()
{
}

void TextureQuad::SetTexture(wstring path)
{
	_material->SetTexture(path);
}

void TextureQuad::CreateResource()
{
	float L = -_size.x * 0.5f;
	float R = +_size.x * 0.5f;
	float B = -_size.y * 0.5f;
	float T = +_size.y * 0.5f;

	vector<VertexTextureLight> vertices;

	vertices =
	{
		{ Vector3(L, T, 0.0f), Vector3(0, 0, -1), Vector3(1.0f, 0.0f, 0.0f), Vector2(0, 0) },
		{ Vector3(R, T, 0.0f), Vector3(0, 0, -1), Vector3(1.0f, 0.0f, 0.0f), Vector2(1, 0) },
		{ Vector3(L, B, 0.0f), Vector3(0, 0, -1), Vector3(1.0f, 0.0f, 0.0f), Vector2(0, 1) },
		{ Vector3(R, B, 0.0f), Vector3(0, 0, -1), Vector3(1.0f, 0.0f, 0.0f), Vector2(1, 1) },
	};
	vector<UINT> indices;

	indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	_mesh->CreateBuffers(vertices, indices);
}