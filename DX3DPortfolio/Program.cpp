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
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (_wireFrame)
		StateManager::Get()->GetRasterizer()->ChangeState(D3D11_FILL_WIREFRAME);
	else
		StateManager::Get()->GetRasterizer()->ChangeState(D3D11_FILL_SOLID);

	Device::Get()->Clear();
	Environment::Get()->SetPerspective();
	_scene->Render();
	Device::Get()->Present();

	ImGui::Checkbox("WrieFrame", &_wireFrame);

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void Program::Initialize()
{
	Device::Get();

	rs = new RasterizerState();
	rs->SetState();

	Camera::Get();
	Environment::Get();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}