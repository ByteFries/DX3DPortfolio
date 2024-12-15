#include "framework.h"
#include "MeshBase.h"

MeshBase::MeshBase(string name)
	:_name(name)
{
}

MeshBase::~MeshBase()
{
	delete _vBuffer;
	delete _iBuffer;
}

void MeshBase::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_iBuffer->IASetBuffer();
	_vBuffer->IASetBuffer(type);
}