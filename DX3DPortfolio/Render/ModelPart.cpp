#include "framework.h"
#include "ModelPart.h"

ModelPart::ModelPart()
{
}

ModelPart::~ModelPart()
{
	delete _vBuffer;
	delete _iBuffer;
	delete _material;
}

void ModelPart::UpdateVertices(void* data, UINT size)
{
	_vBuffer->UpdateVertices(data, size);
}

void ModelPart::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_iBuffer->IASetBuffer();
	_vBuffer->IASetBuffer(type);
	_material->IASetBuffer();
}

void ModelPart::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_iBuffer->IASetBuffer();
	_vBuffer->IASetBuffer(type);
	_material->IASetBuffer();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void ModelPart::RenderInstanced(UINT count)
{
	_iBuffer->IASetBuffer();
	_vBuffer->IASetBuffer();
	_material->IASetBuffer();

	DC->DrawIndexedInstanced(_indices.size(), count, 0, 0, 0);
}
