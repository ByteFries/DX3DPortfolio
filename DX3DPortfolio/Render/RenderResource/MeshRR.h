#pragma once
class MeshRR : public RenderResource
{
public:
	MeshRR() {}
	virtual ~MeshRR();
	// RenderResource을(를) 통해 상속됨
	void SetRenderResources() override;

protected:
	virtual void CreateResource() abstract;

	MeshBase* _mesh;
	Material* _material;
};

