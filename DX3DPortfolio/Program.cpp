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
	Shader::Clear();
	Device::Delete();
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render()
{
	Device::Get()->Clear();
	_scene->Render();
	Device::Get()->Present();
}

void Program::Initialize()
{
	Device::Get();

	D3D11_VIEWPORT viewPort; //화면이 그려질 영역

	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = WIN_WIDTH;
	viewPort.Height = WIN_HEIGHT;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	DC->RSSetViewports(1, &viewPort);
}
