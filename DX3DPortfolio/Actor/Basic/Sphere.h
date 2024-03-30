#pragma once
class Sphere : public Transform
{
public:
	Sphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~Sphere();

	void Update();
	void Render();
	void PostRender();

	StaticMesh* GetMesh() { return _mesh; }

private:
	void CreateVertices();

	vector<VertexTextureNormalMapping> _vertices;
	vector<UINT> _indices;

	StaticMesh* _mesh;

	UINT _sliceCount;
	UINT _stackCount;

	float _radius;
};