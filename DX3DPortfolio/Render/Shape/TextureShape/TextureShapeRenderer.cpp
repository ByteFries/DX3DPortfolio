#include "framework.h"
#include "TextureShapeRenderer.h"

TextureShapeRenderer::TextureShapeRenderer(RendererInterface* renderer)
	:MeshRO(renderer)
{
	_mesh = new StaticMesh();
	_material = new Material();

	SetShader();
}

TextureShapeRenderer::TextureShapeRenderer(wstring path, RendererInterface* renderer)
	:MeshRO(renderer)
{
	_mesh = new StaticMesh();
	_material = new Material();
	_material->SetTexture(path);
	SetShader();
}

std::array<pair<wstring, wstring>, 2> TextureShapeRenderer::GetShaderNames() const
{
	return { 
		{
			{L"TextureLight", L"TextureLight"},
			{L"TextureLightInstancing", L"TextureLight"}
		} 
	};
}