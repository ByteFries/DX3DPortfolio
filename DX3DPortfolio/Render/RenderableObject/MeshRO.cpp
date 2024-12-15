#include "framework.h"
#include "MeshRO.h"

MeshRO::MeshRO(RendererInterface* renderer)
	:RenderableObject(renderer)
{
}

MeshRO::~MeshRO()
{
	delete _mesh;
	delete _material;
}


void MeshRO::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_transform->SetWorld();
	_mesh->IASetBuffer(type);
	_material->IASetBuffer();

	_renderer->Draw(_mesh->GetIndexSize());
}

void MeshRO::SetShader()
{
	const auto shaderNames = GetShaderNames();

	switch (_renderer->GetType())
	{
	case RendererInterface::PEROBJ:
		_material->SetVS(shaderNames[0].first);
		_material->SetPS(shaderNames[1].second);
		break;
	case RendererInterface::INSTANCED:
		_material->SetVS(shaderNames[1].first);
		_material->SetPS(shaderNames[1].second);
		break;
	default:
		break;
	}
}

std::array<pair<wstring, wstring>, 2> MeshRO::GetShaderNames() const
{
	return { {
		{L"Default", L"Default"},
		{L"DefaultInstancing", L"Defualt"}
	} };
}
