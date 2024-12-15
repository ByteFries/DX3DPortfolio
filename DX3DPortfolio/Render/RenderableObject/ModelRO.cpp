#include "framework.h"
#include "ModelRO.h"


ModelRO::ModelRO(RendererInterface* renderer, ModelBase* model)
	:RenderableObject(renderer), _model(model)
{
}

ModelRO::~ModelRO()
{
	delete _model;
}

void ModelRO::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_renderer->Draw(type);
}

void ModelRO::SetModel(ModelBase* model)
{
	delete _model;
	_model = model;
}
