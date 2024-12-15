#include "framework.h"
#include "GridScene.h"

GridScene::GridScene()
{
	_material = new Material();
	_material->SetShader(L"Grid");

	_wBuffer = new WorldBuffer();
	CreateVertices();
}

GridScene::~GridScene()
{
	delete _material;
	delete _wBuffer;
	delete _vBuffer;
}

void GridScene::Update()
{
}

void GridScene::PreRender()
{
}

void GridScene::Render()
{
	_wBuffer->SetVSBuffer(0);
	_material->IASetBuffer();
	_vBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	DC->Draw(_vertices.size(), 0);
}

void GridScene::PostRender()
{
}

void GridScene::CreateVertices()
{
	_vertices.emplace_back(Vector3(-_width, 0, 0), XMFLOAT4(1, 0, 0, 1));
	_vertices.emplace_back(Vector3(+_width, 0, 0), XMFLOAT4(1, 0, 0, 1));

	_vertices.emplace_back(Vector3(0, -_width, 0), XMFLOAT4(0, 1, 0, 1));
	_vertices.emplace_back(Vector3(0, +_width, 0), XMFLOAT4(0, 1, 0, 1));

	_vertices.emplace_back(Vector3(0, 0, -_width), XMFLOAT4(0, 0, 1, 1));
	_vertices.emplace_back(Vector3(0, 0, +_width), XMFLOAT4(0, 0, 1, 1));

	int halfW = _width * 0.5f;
	int halfH = _height * 0.5f;

	for (int x = -halfW; x <= halfW; x += _interval)
	{
		if (x == 0) continue;

		_vertices.emplace_back(Vector3(x, 0, -halfW), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		_vertices.emplace_back(Vector3(x, 0, +halfW), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
	}

	for (int z = -halfH; z <= halfH; z += _interval)
	{
		if (z == 0) continue;

		_vertices.emplace_back(Vector3(-halfH, 0, z), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
		_vertices.emplace_back(Vector3(+halfH, 0, z), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
	}


	_vBuffer = new VertexBuffer(_vertices);
}

void GridScene::Debug()
{
}
