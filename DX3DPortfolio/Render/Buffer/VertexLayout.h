#pragma once

struct Vertex
{
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