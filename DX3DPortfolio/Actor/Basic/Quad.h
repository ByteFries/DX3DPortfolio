#pragma once
class Quad :public Transform
{
public:
	Quad(XMFLOAT2 size);
	~Quad();

	void Render();
	void Update();

private:
	void CreateVertices();

	vector<VertexTexture> _vertices;
	vector<UINT> _indices;

	XMFLOAT2 _size;

	StaticMesh* _mesh;
};

