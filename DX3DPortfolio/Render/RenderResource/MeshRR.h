#pragma once
class MeshRR : public RenderResource
{
public:
	MeshRR() {}
	virtual ~MeshRR();
	// RenderResource��(��) ���� ��ӵ�
	void SetRenderResources() override;

protected:
	virtual void CreateResource() abstract;

	MeshBase* _mesh;
	Material* _material;
};

