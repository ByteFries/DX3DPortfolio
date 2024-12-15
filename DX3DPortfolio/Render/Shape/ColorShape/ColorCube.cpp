#include "framework.h"
#include "ColorCube.h"

ColorCube::ColorCube(Vector3 size, XMFLOAT4 color, RendererInterface* renderer)
	:ColorShapeRenderer(renderer), _size(size)
{
	CreateResource();
	SetColor(color);
}

ColorCube::~ColorCube()
{
	for (ColorQuad* q : _surfaces)
		delete q;

	_surfaces.clear();
}

void ColorCube::SetColor(XMFLOAT4 color)
{
	for (ColorQuad* quad : _surfaces)
	{
		quad->SetColor(color);
	}
}

void ColorCube::Update()
{
	_transform->Update();

	for (ColorQuad* quad : _surfaces)
		quad->Update();
}

void ColorCube::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	for (ColorQuad* quad : _surfaces)
	{
		quad->Render(type);
	}
}

void ColorCube::CreateResource()
{
	//F
	{
		ColorQuad* quad = new ColorQuad(Vector2(_size.x, _size.y));
		Transform* transform = new Transform();

		transform->_translation.z += _size.z * 0.5f;
		transform->_rotation.x += 3.141592f;
		transform->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//B
	{
		ColorQuad* quad = new ColorQuad(Vector2(_size.x, _size.y));
		quad->GetTransform()->_translation.z -= _size.z * 0.5f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//T
	{
		ColorQuad* quad = new ColorQuad(Vector2(_size.x, _size.z));
		quad->GetTransform()->_translation.y += _size.y * 0.5f;
		quad->GetTransform()->_rotation.x += 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//D
	{
		ColorQuad* quad = new ColorQuad(Vector2(_size.x, _size.z));
		quad->GetTransform()->_translation.y -= _size.y * 0.5f;
		quad->GetTransform()->_rotation.x -= 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//L
	{
		ColorQuad* quad = new ColorQuad(Vector2(_size.z, _size.y));
		quad->GetTransform()->_translation.x -= _size.x * 0.5f;
		quad->GetTransform()->_rotation.y = 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}

	//R
	{
		ColorQuad* quad = new ColorQuad(Vector2(_size.z, _size.y));
		quad->GetTransform()->_translation.x += _size.x * 0.5f;
		quad->GetTransform()->_rotation.y -= 90.0f * 3.141592f / 180.0f;
		quad->GetTransform()->SetParent(_transform);
		_surfaces.push_back(quad);
	}
}
