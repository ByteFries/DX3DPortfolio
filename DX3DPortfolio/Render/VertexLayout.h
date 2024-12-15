#pragma once

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z)
		:pos(x, y, z)
	{}


	Vector3 pos;
};

struct VertexColor
{
	VertexColor() :pos(0, 0, 0), color(1, 1, 1, 1) {}
	VertexColor(Vector3 pos, XMFLOAT4 color)
		:pos(pos), color(color)
	{}

	Vector3 pos;
	XMFLOAT4 color;
};

struct VertexLight
{
	VertexLight() {}
	VertexLight(Vector3 pos, Vector3 normal) :pos(pos), normal(normal) {}

	Vector3 pos;
	Vector3 normal;
};

struct VertexColorLight
{
	VertexColorLight() :pos(0, 0, 0), color(1, 1, 1, 1), normal(0, 0, 0) {}

	VertexColorLight(Vector3 pos, XMFLOAT4 color, Vector3 normal)
		:pos(pos), color(color), normal(normal) {}

	Vector3 pos;
	XMFLOAT4 color;
	Vector3 normal;
};

struct VertexTextureLight
{
	VertexTextureLight() :pos(), normal(), tangent(), uv() {}
	VertexTextureLight(Vector3 pos, Vector3 normal, Vector3 tangent, Vector2 uv)
		:pos(pos), normal(normal), tangent(tangent), uv(uv) {}

	Vector3 pos;
	Vector3 normal;
	Vector3 tangent;
	Vector2 uv;
};

struct SkeletalMeshVertex
{
	SkeletalMeshVertex() {}

	Vector3 pos = {};
	Vector3 normal = {};
	Vector3 tangent = {};
	Vector3 bitangent = {};
	Vector2 uv = {};

	XMFLOAT4 indices = {};
	XMFLOAT4 weights = {};
};

struct StaticMeshVertex
{
	StaticMeshVertex() {}
	
	Vector3 pos = {};
	Vector3 normal = {};
	Vector3 tangent = {};
	Vector3 bitangent = {};
	Vector2 uv = {};
};