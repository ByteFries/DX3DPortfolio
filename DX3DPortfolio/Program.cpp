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
}

void Program::Render()
{
}

void Program::Initialize()
{
	Device::Get();
}
