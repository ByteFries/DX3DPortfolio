#pragma once
class StaticMesh :public Mesh
{
public:
	StaticMesh(string name);
	StaticMesh();
	virtual ~StaticMesh();

protected:
	virtual void ReadMesh() override;
};
