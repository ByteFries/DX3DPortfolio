#pragma once
class Watcher : public Actor
{
public:
	Watcher();
	~Watcher();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

private:
	RenderTarget* _renderTarget;
	DepthStencil* _depthStencil;
	Quad* _screen;
	class Camera* _camera;

};

