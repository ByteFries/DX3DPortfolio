#pragma once
class Terrain : public Transform
{
public:
	Terrain(XMFLOAT2 size);
	Terrain(wstring HeightMap);
	~Terrain();

	void Update();
	void Render();

	Material* GetMaterial() { return _mesh->GetPart(0)->GetMaterial(); }

	bool Picking(Vector3 input, OUT Vector3* position);

	bool GetHeight(Vector3 pos, float& height);

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

	StaticMesh* _mesh;

	Texture* _heightMap;
	const float MAP_HEIGHT = 20.0f;
};