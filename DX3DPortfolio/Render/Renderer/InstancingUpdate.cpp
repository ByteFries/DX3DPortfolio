#include "framework.h"
#include "InstancingUpdate.h"

void InstancingUpdate::Update(RendererInterface* renderer)
{
	InstancedRenderer* instancedRenderer = static_cast<InstancedRenderer*>(renderer);

	if (instancedRenderer != nullptr)
	{
		//instancedRenderer->UpdateInstanceData();
	}
	//auto instanceData = renderer->
}
