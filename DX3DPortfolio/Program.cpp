#include "framework.h"
#include "Program.h"
#include "Scene\MainScene.h"

Program::Program()
{
	Initialize();
	_scene = new MainScene();
}

Program::~Program()
{
	delete _scene;
	delete rs;
	Shader::Clear();
	Texture::Delete();
	Environment::Delete();
	Camera::Delete();
	Device::Delete();
}

void Program::Update()
{
	Time::Get()->Update();
	Keyboard::Get()->Update();
	Camera::Get()->Update();
	_scene->Update();
}

void Program::Render()
{
	Device::Get()->Clear();
	Environment::Get()->SetPerspective();
	_scene->Render();
	Device::Get()->Present();
}

void Program::Initialize()
{
	Device::Get();

	rs = new RasterizerState();
	rs->SetState();

	Camera::Get();
	Environment::Get();
}
