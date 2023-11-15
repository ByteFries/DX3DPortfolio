#pragma once

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}

	Vector3 pos;
};

struct VertexTexture
{
	Vector3 pos;
	XMFLOAT2 uv;
};

struct VertexTextureNormal
{
	Vector3 pos;
	XMFLOAT2 uv;
	Vector3 normal;
};

struct VertexTextureNormalMapping
{
	Vector3 pos;
	XMFLOAT2 uv;
	Vector3 normal;
	Vector3 tangent;
};

struct VertexTextureNormalTangentBlend
{
	Vector3 pos = {};
	XMFLOAT2 uv = {};
	Vector3 normal = {};
	Vector3 tangent = {};
	XMFLOAT4 indices = {};
	XMFLOAT4 weights = {};
};