#include "framework.h"
#include "Program.h"
bool Program::test = false;
Program::Program()
{
	Initial();
}

Program::~Program()
{
	Device::Delete();
	Shader::Clear();
	Texture::Delete();
	Time::Delete();
	Keyboard::Delete();
	StateManager::Delete();
	PhysicsManager::Delete();
	Environment::Delete();
	CameraManager::Delete();
	SceneManager::Delete();
	LightManager::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Program::Update()
{
	TIME->Update();
	KEYBOARD->Update();
	CAMERA->Update();
	PHYSICS->Update();
	SCENE->Update();
	LIGHT->Update();
}

void Program::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Device::Get()->Clear();

	ENVIRONMENT->SetViewport();
	ENVIRONMENT->SetEnvrionment();
	LIGHT->SetLight();
	SCENE->Render();
	PHYSICS->Render();
	SCENE->PostRender();

	ENVIRONMENT->Debug();
	PHYSICS->Debug();
	SCENE->Debug();
	TIME->Debug();
	
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void Program::Initial()
{
	Device::Get();
	ENVIRONMENT;
	KEYBOARD;
	STATE;
	CAMERA;
	PHYSICS;
	SCENE;
	LIGHT;
	TIME->LockFPS(60);

	PHYSICS->StartInitial();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}
