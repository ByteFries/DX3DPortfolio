#pragma once
class Terrain : public Transform
{
public:
	Terrain();
	~Terrain();

	void Update();
	void Render();

private:
	vector<VertexTextureNormal> _vertices;
	vector<UINT> _indices;

	void CreateVertices();

	float _width = 256;
	float _height = 256;

	Mesh* _mesh;
	Material* _material;

	const float MAP_HEIGHT = 20.0f;
};