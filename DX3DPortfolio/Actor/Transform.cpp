#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
	_wBuffer = new WorldBuffer();
}

Transform::~Transform()
{
	delete _wBuffer;
}

void Transform::Update()
{
	_srt = XMMatrixTransformation
	(
		_pivot, 
		XMQuaternionIdentity(),
		_scale,
		_pivot, 
		XMQuaternionRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z),
		_translation
	);

	if (_parent != nullptr)
		_srt *= _parent->GetSRT();

	_wBuffer->SetMatrix(_srt);

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, _srt);

	_right = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	_up = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	_forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();

	XMVECTOR S, R, T;

	XMMatrixDecompose(&S, &R, &T, _srt);

	_worldScale = S;
	_worldRotation = R;
	_worldTranslation = T;
}

void Transform::Debug()
{
	ImGui::DragFloat3("Scale", (float*)&_scale, 0.01f, 0.01f, 100.0f);
	//ImGui::DragFloat3("Rotation",    (float*)&rotation,    0.01f,    -XM_2PI,    XM_2PI);

	ImGui::SliderAngle("RotationX", &_rotation.x);
	ImGui::SliderAngle("RotationY", &_rotation.y);
	ImGui::SliderAngle("RotationZ", &_rotation.z);

	ImGui::DragFloat3("Translation", (float*)&_translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);

	//if (ImGui::BeginMenu("transform"))
	//{
	//	
	//
	//	ImGui::EndMenu();
	//}
}
