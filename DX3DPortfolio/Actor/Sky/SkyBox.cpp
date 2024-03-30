#include "framework.h"
#include "SkyBox.h"

SkyBox::SkyBox()
{
	_sphere = new Sphere(500, 20, 10);

	_sphere->GetMesh()->SetShader(L"Sky");

	_sBuffer = new SkyBuffer();

	_rs = new RasterizerState();

	_rs->FrontCounterClockWise(true);
}

SkyBox::~SkyBox()
{
	delete _rs;
	delete _sphere;
	delete _sBuffer;
}

void SkyBox::Update()
{
}

void SkyBox::Render()
{
	_sBuffer->SetPSBuffer(10);

	_rs->SetState();

	StateManager::Get()->DepthDisable();

	_sphere->Render();

	RS->SetState();

	StateManager::Get()->DepthEnable();
}

void SkyBox::Debug()
{
	if (ImGui::TreeNode("Sky Option"))
	{
		ImGui::ColorEdit3("Center Color", (float*)&_sBuffer->_data.centerColor, ImGuiColorEditFlags_PickerHueBar);
		ImGui::ColorEdit3("Apex   Color", (float*)&_sBuffer->_data.apexColor, ImGuiColorEditFlags_PickerHueWheel);
		ImGui::DragFloat("Height", &_sBuffer->_data.height);

		ImGui::TreePop();
	}
}
