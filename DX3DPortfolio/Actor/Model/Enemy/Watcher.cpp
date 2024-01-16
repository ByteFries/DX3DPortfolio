#include "framework.h"
#include "Watcher.h"

Watcher::Watcher()
	:Actor("Drone")
{
	_label = "Watcher";

	_renderTarget = new RenderTarget();
	_depthStencil = new DepthStencil();
	_screen = new Quad(XMFLOAT2(10, 6));
	
	_screen->GetMesh()->GetMaterial(0)->SetDiffuseMap(Texture::Get(L"WatcherS", _renderTarget->GetSRV()));
	_screen->GetMesh()->GetMaterial(0)->SetShader(L"Default");
	
	_camera = CAMERA->CreateCamera();
	_camera->SetLabel("WatcherCam");

	_camera->SetParent(this);
	_camera->SetCameraMode(Camera::STATIC);
	_camera->_translation.y = 12.0f;
	_camera->_translation.z = 4.0f;

	_screen->SetParent(this);
	_screen->_rotation.y = XM_PI;
	_screen->_translation.y = 3.5f;
	_screen->_translation.z = 0.3f;
	_screen->GetMesh()->GetMaterial(0)->GetMaterialBuffer()->SetLightAffect(false);
	_screen->SetLabel("Screen");

	_mesh = new StaticMesh();
}

Watcher::~Watcher()
{
	delete _renderTarget;
	delete _depthStencil;
	delete _screen;
	delete _mesh;
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
	Environment::Get()->SetEnvironment();
}

void Watcher::Render()
{
	MAIN_CAMERA->SetVSBuffer(1);
	Environment::Get()->SetEnvironment();

	Actor::Render();

	_screen->Render();
}

void Watcher::PostRender()
{
}

void Watcher::Debug()
{
	Transform::Debug();
	
	_screen->Debug();
}
