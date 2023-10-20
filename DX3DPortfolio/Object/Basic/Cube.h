#pragma once
class Cube :public Transform
{
public:
	Cube();
	~Cube();

	void Update();
	void Render();

private:
	void CreateVertices();

	Vector3 _size = {10.0f, 10.0f, 10.0f};

	vector<Vertex> _vertices;
	vector<UINT> _indices;

	Mesh* _mesh;
	Material* _material;
};

