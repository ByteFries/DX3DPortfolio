#include "framework.h"
#include "MeshRR.h"


MeshRR::~MeshRR()
{
	delete _mesh;
	delete _material;
}

void MeshRR::SetRenderResources()
{
	_mesh->IASetBuffer();
	_material->IASetBuffer();
}
