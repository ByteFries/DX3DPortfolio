#pragma once
#include "Render/Renderer/RendererInterface.h"
class InstancedRenderer : public RendererInterface
{
public:
	InstancedRenderer(VertexBuffer* instanceBuffer, UINT drawCount);
	virtual ~InstancedRenderer();

	void Draw(int indexCounter) override;
	
	void UpdateInstanceData(vector<InstanceDataBase*>& data, UINT drawCount);

	RendererType GetType() override { return INSTANCED; }
protected:
	VertexBuffer* _instanceBuffer;
	UINT _drawCount = 0;
};