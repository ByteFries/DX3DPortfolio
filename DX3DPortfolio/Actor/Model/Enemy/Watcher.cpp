#include "framework.h"
#include "Watcher.h"

Watcher::Watcher()
	:Actor("Drone5")
{
	_scale *= 0.01f;
	_renderTarget = new RenderTarget();
	_depthStencil = new DepthStencil();
	_screen = new Quad(XMFLOAT2(450, 300));
	
	_screen->GetMesh()->GetPart(0)->GetMaterial()->SetDiffuseMap(Texture::Get(L"WatcherS", _renderTarget->GetSRV()));
	_screen->GetMesh()->GetPart(0)->GetMaterial()->SetShader(L"Reflection");
	
	_camera = CAMERA->CreateCamera();
	_camera->SetTarget(this);
	//_camera->_rotation.y = XM_PI;
	//_camera->_translation.y += 10.0f;
	//_camera->_translation.z += 5.0f;
	_screen->SetParent(this);
	_screen->_rotation.y = XM_PI;
	_screen->_translation.z += 20;
}

Watcher::~Watcher()
{
	delete _renderTarget;
	delete _depthStencil;
	delete _screen;
}

void Watcher::Update()
{
	Actor::Update();
	_screen->Update();
}

void Watcher::PreRender()
{
	_renderTarget->Set(_depthStencil, { 0.2f,0.2f,0.2f,1.0f });

	_camera->SetView();
}

void Watcher::Render()
{
	_camera->SetVSBuffer(10);
	DC->PSSetShaderResources(10, 1, &_renderTarget->GetSRVRef());

	Actor::Render();

	_screen->Render();
}

void Watcher::PostRender()
{
}
