#pragma once
class SkeletalMesh : public MeshBase
{
public:
	SkeletalMesh(string name = "Main");
	~SkeletalMesh();

	bool ImportMeshData() override;
private:
};