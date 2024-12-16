#include "framework.h"
#include "InstancedRenderer.h"

InstancedRenderer::InstancedRenderer(InstanceBuffer* instanceBuffer, UINT drawCount)
	:_instanceBuffer(instanceBuffer), _drawCount(drawCount)
{
}

InstancedRenderer::~InstancedRenderer()
{
	delete _instanceBuffer;
}

void InstancedRenderer::Draw(int indexCounter)
{
	_instanceBuffer->IASetBuffer();
	DC->DrawIndexedInstanced(indexCounter, _drawCount, 0, 0, 0);
}

void InstancedRenderer::UpdateInstanceData(vector<InstanceDataBase*>& data, UINT drawCount)
{
	vector<void*> rawData;

	for (const auto& instance : data)
	{
		rawData.push_back(instance->GetData());
	}

	_drawCount = drawCount;
	_instanceBuffer->Update(rawData.data(), _drawCount);
}