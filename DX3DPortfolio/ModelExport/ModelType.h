#pragma once

typedef VertexTextureNormalTangentBlend ModelVertex;

struct MeshData
{
	string name;

	UINT materialIndex;

	vector<ModelVertex> vertices;
	vector<UINT>         indices;
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
	XMFLOAT4 rotation;
	Vector3 position;
};

struct SequenceTransforms
{
	XMMATRIX transform[MAX_FRAME_KEY][MAX_BONE];
};

struct KeySRT
{
	XMFLOAT4 scale;
	XMFLOAT4 rotate;
	XMFLOAT4 translation;
};

struct SequenceSRT
{
	KeySRT SRTs[MAX_FRAME_KEY][MAX_BONE];
};