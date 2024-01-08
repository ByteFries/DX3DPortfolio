#include "framework.h"
#include "ModelPart.h"

ModelPart::ModelPart()
{
}

ModelPart::~ModelPart()
{
	delete _vBuffer;
	delete _iBuffer;
}

void ModelPart::UpdateVertices(void* data, UINT size)
{
	_vBuffer->UpdateVertices(data, size);
}

void ModelPart::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_iBuffer->IASetBuffer();
	_vBuffer->IASetBuffer(type);
}

void ModelPart::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_iBuffer->IASetBuffer();
	_vBuffer->IASetBuffer(type);

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void ModelPart::RenderInstanced(UINT count)
{
	_iBuffer->IASetBuffer();
	_vBuffer->IASetBuffer();

	DC->DrawIndexedInstanced(_indices.size(), count, 0, 0, 0);
}
