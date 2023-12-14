#pragma once
class SkeletalMesh : public StaticMesh
{
public:
	SkeletalMesh();
	~SkeletalMesh();

	virtual void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;

private:

};