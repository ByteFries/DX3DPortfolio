#include "framework.h"
#include "SkySphere.h"

SkySphere::SkySphere(float rad, UINT stack, UINT slice, wstring path)
{
	_sphere = new TextureSphere(rad, stack, slice, path);
	_sphere->GetTransform()->SetParent(_transform);
	_sphere->GetMaterial()->GetMatBuffer()->SetLightAffect(false);
	_rs = new RasterizerState();
	_rs->FrontCounterClockWise(true);
}

SkySphere::~SkySphere()
{
	delete _sphere;
	delete _rs;
}

void SkySphere::Update()
{
	_transform->Update();
	_sphere->Update();
}

void SkySphere::Render()
{
	_rs->SetState();

	_sphere->Render();

	STATE->SetRS();
}

void SkySphere::Debug()
{
	if (ImGui::TreeNode("Sky"))
	{
		auto transform = _sphere->GetTransform();
		ImGui::Begin("Rotation Editor");
		ImGui::SliderFloat("X", &transform->_rotation.x, -XM_PI, XM_PI, "%.2f");
		ImGui::SliderFloat("Y", &transform->_rotation.y, -XM_PI, XM_PI, "%.2f");
		ImGui::SliderFloat("Z", &transform->_rotation.z, -XM_PI, XM_PI, "%.2f");
		ImGui::End();

		ImGui::TreePop();
	}
}
