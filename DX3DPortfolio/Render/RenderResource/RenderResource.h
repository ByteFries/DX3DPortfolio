#pragma once
class RenderResource
{
public:
	RenderResource();
	virtual ~RenderResource();

	virtual void SetRenderResources() abstract;
};