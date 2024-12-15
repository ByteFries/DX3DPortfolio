#pragma once
class TerrainQuad
{
public:
	TerrainQuad(Vector2 size = { 50.0f, 50.0f });
	~TerrainQuad();

	void Render();
	void Update();

private:
	TextureQuad* _quad;
};