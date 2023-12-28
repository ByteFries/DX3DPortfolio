#include "framework.h"
#include "Program.h"
#include "Scene\MainScene.h"

Program::Program()
{
	Initialize();
	Time::Get()->LockFPS(60.0f);
	_scene = new MainScene();
}

Program::~Program()
{
	delete _scene;
	Device::Delete();
	Shader::Clear();
	Time::Delete();
	Environment::Delete();
	Keyboard::Delete();
	StateManager::Delete();
	
	Texture::Delete();
	CameraManager::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Program::Update()
{
	Time::Get()->Update();
	Keyboard::Get()->Update();
	CAMERA->Update();
	_scene->Update();
}

void Program::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (KEY_DOWN(VK_SPACE))
	{
		mouseFocus = !mouseFocus;
		ShowCursor(!mouseFocus);
	}

	if (_wireFrame)
		StateManager::Get()->GetRasterizer()->ChangeState(D3D11_FILL_WIREFRAME);
	else
		StateManager::Get()->GetRasterizer()->ChangeState(D3D11_FILL_SOLID);

	_scene->PreRender();

	Device::Get()->Clear();

	Environment::Get()->SetViewport();
	//Environment::Get()->SetPerspective();


	Environment::Get()->SetEnvironment();

	_scene->Render();
	_scene->PostRender();

	ImGui::Checkbox("WireFrame", &_wireFrame);
	Time::Get()->Debug();

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void Program::Initialize()
{
	Device::Get();

	CAMERA;
	Environment::Get();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}