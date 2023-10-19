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
	Device::Delete();
	delete _scene;
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render()
{
	_scene->Render();
}

void Program::Initialize()
{
	Device::Get();
}
