#pragma once
class RenderableObject
{
public:
	RenderableObject(RendererInterface* renderer);
	virtual ~RenderableObject();

	virtual void Update();
	virtual void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) abstract;

	void SetRenderer(RendererInterface* renderer);

	RendererInterface* GetRenderer() { return _renderer; }
	Transform* GetTransform() { return _transform; }
protected:
	RendererInterface* _renderer;
	Transform* _transform;
};
