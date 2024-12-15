#include "framework.h"
#include "RenderableObject.h"

RenderableObject::RenderableObject(RendererInterface* renderer)
	:_renderer(renderer)
{
	_transform = new Transform;
}

RenderableObject::~RenderableObject()
{
	delete _renderer;
	delete _transform;
}

void RenderableObject::Update()
{
	_transform->Update();
}

void RenderableObject::SetRenderer(RendererInterface* renderer)
{
	delete _renderer;
	_renderer = renderer;
}
