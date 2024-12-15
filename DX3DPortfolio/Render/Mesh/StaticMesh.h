#pragma once
class StaticMesh : public MeshBase
{
public:
	StaticMesh(string name = "Main");
	~StaticMesh();

	bool ImportMeshData() override;
private:

};