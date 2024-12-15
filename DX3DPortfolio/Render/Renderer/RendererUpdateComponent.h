#pragma once
class RendererInterface;
class RendererUpdateComponent
{
public:
	RendererUpdateComponent() {}
	virtual ~RendererUpdateComponent() {}

	virtual void Update(RendererInterface* renderer) abstract;
};