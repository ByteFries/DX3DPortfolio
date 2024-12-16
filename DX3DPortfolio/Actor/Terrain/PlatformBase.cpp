#include "framework.h"
#include "PlatformBase.h"

PlatformBase::PlatformBase()
{
}

PlatformBase::~PlatformBase()
{
	delete _render;
}

void PlatformBase::Update()
{
	_transform->Update();
	_render->Update();
}

void PlatformBase::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_render->Render(type);
}