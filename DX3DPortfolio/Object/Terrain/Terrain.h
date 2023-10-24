#pragma once
class Terrain : public Transform
{
public:
	Terrain();
	~Terrain();

	void Update();
	void Render();

private:
	vector<VertexTexture> _vertices;
	vector<UINT> _indices;

	void CreateVertices();

	float _width = 256;
	float _height = 256;

	Mesh* _mesh;
	Material* _material;
};