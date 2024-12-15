#pragma once
class MeshRO : public RenderableObject
{
public:
	MeshRO(RendererInterface* renderer = new PerObjectRenderer);
	virtual ~MeshRO();

	void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;
	Material* GetMaterial() { return _material; }
	MeshBase* GetMesh() { return _mesh; }
protected:
	void SetShader();
	virtual std::array<pair<wstring, wstring>,2> GetShaderNames() const;
	virtual void CreateResource() abstract;
	MeshBase* _mesh;
	Material* _material;
};

