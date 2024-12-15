#pragma once
class ModelRO : public RenderableObject
{
public:
	ModelRO(RendererInterface* renderer, ModelBase* model);
	virtual ~ModelRO();

	void Render(D3D11_PRIMITIVE_TOPOLOGY type) override;

	void SetModel(ModelBase* model);

protected:
	ModelBase* _model;
};