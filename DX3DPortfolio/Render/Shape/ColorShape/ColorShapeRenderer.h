#pragma once
class ColorShapeRenderer : public MeshRO
{
public:
	ColorShapeRenderer(RendererInterface* renderer = new PerObjectRenderer);
	virtual ~ColorShapeRenderer();
	void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;
	void SetColor(XMFLOAT4 val) { _cBuffer->SetColor(val); }
protected:
	std::array<pair<wstring, wstring>, 2> GetShaderNames() const override;

	ColorBuffer* _cBuffer;
};
