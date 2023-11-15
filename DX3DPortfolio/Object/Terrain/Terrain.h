#pragma once
class Terrain : public Transform
{
public:
	Terrain();
	~Terrain();

	void Update();
	void Render();

	bool Picking(Vector3 input, OUT Vector3* position);

private:
	void CreateVertices();

	void CreateCompute();

	struct InputDesc
	{
		UINT index;
		Vector3 v0, v1, v2;
	};
	
	struct OutputDesc
	{
		int isPicked = 0;
		float u, v;
		float distance;
	};

	InputDesc* _input;
	OutputDesc* _output;

	UINT _polygonCount;
	Vector3 _pickedPos;

	ComputeShader* _cShader;
	RayBuffer* _rBuffer;
	StructuredBuffer* _sBuffer;

	vector<VertexTextureNormalMapping> _vertices;
	vector<UINT> _indices;

	float _width = 256;
	float _height = 256;

	Mesh* _mesh;
	Material* _material;

	const float MAP_HEIGHT = 20.0f;
};