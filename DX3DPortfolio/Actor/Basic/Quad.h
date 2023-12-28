#pragma once
class Quad :public Transform
{
public:
	Quad(XMFLOAT2 size);
	~Quad();

	void Render();
	void Update();
	
	StaticMesh* GetMesh() { return _mesh; }
private:
	void CreateVertices();

	vector<VertexTextureNormalTangentBlend> _vertices;
	vector<UINT> _indices;

	XMFLOAT2 _size;

	StaticMesh* _mesh;
};

