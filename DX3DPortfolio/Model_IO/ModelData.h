#pragma once

struct MeshData
{
	string name;
	UINT materialIndex;
	vector<UINT> indices;
	bool hasBone;

	virtual void resize(int size) abstract;
	virtual void SetVertex(int index, SkeletalMeshVertex vertex) abstract;
	virtual void WriteToFile(const string& path) abstract;
};

struct StaticMeshData : public MeshData
{
	vector<StaticMeshVertex> vertices;

	virtual void resize(int size) override
	{
		vertices.resize(size);
	}

	virtual void SetVertex(int index, SkeletalMeshVertex val) override
	{
		StaticMeshVertex vertex;
		vertex.pos = val.pos;
		vertex.normal = val.normal;
		vertex.tangent = val.tangent;
		vertex.bitangent = val.bitangent;
		vertex.uv = val.uv;
		
		vertices[index] = vertex;
	}

	virtual void WriteToFile(const string& path) override
	{
		BinaryWriter writer(path);
		writer.WriteData(materialIndex);

		writer.WriteData((int)0); //hasBone->false
		writer.WriteData((UINT)vertices.size());
		writer.WriteData(vertices.data(), vertices.size() * sizeof(StaticMeshVertex));

		writer.WriteData((UINT)indices.size());
		writer.WriteData(indices.data(), indices.size() * sizeof(UINT));
	}
};

struct SkeletalMeshData : public MeshData
{
	vector<SkeletalMeshVertex> vertices;

	virtual void resize(int size) override
	{
		vertices.resize(size);
	}

	virtual void SetVertex(int index, SkeletalMeshVertex vertex) override
	{
		vertices[index] = vertex;
	}

	void WriteToFile(const string& path) override
	{
		BinaryWriter writer(path);
		writer.WriteData(materialIndex);

		writer.WriteData((int)1); //hasBone->true
		writer.WriteData((UINT)vertices.size());
		writer.WriteData(vertices.data(), vertices.size() * sizeof(SkeletalMeshVertex));

		writer.WriteData((UINT)indices.size());
		writer.WriteData(indices.data(), indices.size() * sizeof(UINT));
	}
};

struct NodeData
{
	int index;

	string name;

	int parent;

	XMMATRIX transform;
};

struct BoneData
{
	int index;

	string name;

	XMMATRIX offset;
};

struct VertexWeights
{
	UINT indices[4];
	float weights[4];

	void Add(const UINT& index, const float& weight)
	{
		for (UINT i = 0; i < 4; i++)
		{
			if (weights[i] == 0.0f)
			{
				indices[i] = index;
				weights[i] = weight;
				return;
			}
		}
	}

	void Normalize()
	{
		float sum = 0.0f;

		for (UINT i = 0; i < 4; i++)
		{
			sum += weights[i];
		}

		for (UINT i = 0; i < 4; i++)
		{
			weights[i] /= sum;
		}
	}
};

struct KeyTransform
{
	float time;

	Vector3 scale;
	XMFLOAT4 quaternion;
	Vector3 position;
};

struct ClipData
{
	string savePath;
	string name;
	UINT frameCount;
	float ticksPerSecond;
	float duration;
	unordered_map<string, vector<KeyTransform>> keyTransforms;
};

struct SequenceTransforms
{
	XMMATRIX transform[MAX_FRAME_KEY][MAX_BONE];
};