#include "framework.h"
#include "ColorShapeRenderer.h"

ColorShapeRenderer::ColorShapeRenderer(RendererInterface* renderer)
	:MeshRO(renderer)
{
	_mesh = new StaticMesh();
	_material = new Material();
	_cBuffer = new ColorBuffer();
	SetShader();
}

ColorShapeRenderer::~ColorShapeRenderer()
{
	delete _cBuffer;
}

void ColorShapeRenderer::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	// 0 = lightBuffer
	_cBuffer->SetPSBuffer(2);
	//1 = materialBuffer
	MeshRO::Render(type);
}

std::array<pair<wstring, wstring>, 2> ColorShapeRenderer::GetShaderNames() const
{
	return 
	{ 
		{
			{L"ColorLight", L"ColorLight"},
			{L"ColorLightInstancing", L"ColorLight"}
		} 
	};
}
