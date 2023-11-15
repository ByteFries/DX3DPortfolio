#pragma once

typedef VertexTextureNormalTangentBlend ModelVertex;

class ModelMesh
{
public:
	ModelMesh();
	~ModelMesh();

	void Create();

	void Render();
	void RenderInstanced(UINT instanceCount);

	string GetName() { return _name; }
	Material* GetMaterial() { return _material; }

	vector<VertexTextureNormalTangentBlend>& GetVertices() { return _vertices; }
	vector<UINT>& GetIndices() { return _indices; }

	void SetName(string name) { _name = name; }
	void SetVertices(vector<ModelVertex> vertices) {_vertices = vertices;}
	void SetIndices(vector<UINT> indices) { _indices = indices; }
	void SetMesh(Mesh* mesh) { _mesh = mesh; }
	void SetMaterial(Material* material) { _material = material; }

private:
	string _name;
	Material* _material;
	Mesh* _mesh;
	vector<ModelVertex> _vertices;
	vector<UINT>         _indices;
};

