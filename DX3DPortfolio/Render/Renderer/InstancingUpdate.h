#pragma once
#include "Render\Renderer\InstancedRenderer.h"

class InstancingUpdate : public RendererUpdateComponent
{
	void Update(RendererInterface* renderer) override;
};