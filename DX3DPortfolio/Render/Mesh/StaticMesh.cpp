#include "framework.h"
#include "StaticMesh.h"

StaticMesh::StaticMesh(string name)
    :MeshBase(name)
{
}

StaticMesh::~StaticMesh()
{
}

bool StaticMesh::ImportMeshData()
{
    return false;
}
