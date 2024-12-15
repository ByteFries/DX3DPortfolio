#include "framework.h"
#include "TerrainQuad.h"

TerrainQuad::TerrainQuad(Vector2 size)
{
	_quad = new TextureQuad(size);
	//_quad->GetTransform()->_rotation.x = XM_PIDIV2;
}

TerrainQuad::~TerrainQuad()
{
	delete _quad;
}

void TerrainQuad::Render()
{
	//_quad->Render();
}

void TerrainQuad::Update()
{
	_quad->Update();
}
