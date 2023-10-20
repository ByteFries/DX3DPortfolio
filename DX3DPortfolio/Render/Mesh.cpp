#include "framework.h"
#include "Mesh.h"

Mesh::~Mesh()
{
	delete _vBuffer;
	delete _iBuffer;
}

void Mesh::UpdateVertices(void* data, UINT size)
{
	_vBuffer->UpdateVertices(data, size);
}

void Mesh::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_vBuffer->IASetBuffer(type);
	_iBuffer->IASetBuffer();
}