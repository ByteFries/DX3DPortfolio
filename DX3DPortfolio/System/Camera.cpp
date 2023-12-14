#include "framework.h"
#include "Camera.h"

Camera::Camera()
{
	_view = new CameraBuffer();
}

Camera::~Camera()
{
	delete _view;
}

void Camera::Update()
{
	if (!_target)
		FreeMode();
	else
		TargetMode();
}

Ray Camera::ScreenPointToRay(Vector3 pos)
{
	Ray ray;
	ray.origin = _translation;

	Vector3 point;

	point.x = +(2.0f * pos.x) / WIN_WIDTH - 1.0f;
	point.y = -(2.0f * pos.y) / WIN_HEIGHT + 1.0f;
	point.z = 1.0f;

	XMMATRIX projMatrix = Environment::Get()->GetPersMatrix();

	XMFLOAT4X4 proj;

	XMStoreFloat4x4(&proj, projMatrix);

	point.x /= proj._11;
	point.y /= proj._22;

	XMMATRIX invView = _srt;

	ray.direction = point * invView;
	ray.direction.Normalize();

	return ray;
}

void Camera::Debug()
{
	Transform::Debug();

	if (ImGui::TreeNode("Camera Option"))
	{

		ImGui::Text("Camera Pos : %.3f, %.3f, %.3f", _translation.x, _translation.y, _translation.z);
		ImGui::Text("Camera Rot : %.3f, %.3f, %.3f", _rotation.x, _rotation.y, _rotation.z);

		Transform::Debug();

		ImGui::SliderFloat("Height", &_targetHeight, -10.0f, 100.0f);
		ImGui::SliderFloat("Distance", &_targetDistance, -10.0f, 100.0f);


		ImGui::TreePop();
	}
}

void Camera::FreeMode()
{
	//if (!KEY_PRESS(VK_LBUTTON))
		//return;

	if (KEY_PRESS('W'))
	{
		_translation += DELTA * _cameraSpeed * _forward;
	}
	if (KEY_PRESS('S'))
	{
		_translation += DELTA * _cameraSpeed * -1 * _forward;
	}
	if (KEY_PRESS('A'))
	{
		_translation += DELTA * _cameraSpeed * -1 * _right;
	}
	if (KEY_PRESS('D'))
	{
		_translation += DELTA * _cameraSpeed * _right;
	}
	if (KEY_PRESS('Q'))
	{
		_translation.y += DELTA * _cameraSpeed;
	}
	if (KEY_PRESS('E'))
	{
		_translation.y -= DELTA * _cameraSpeed;
	}

	if (KEY_PRESS(VK_LBUTTON))
	{
		Vector3 dir = (mousePos - _oldMousePos).GetNormalized();

		_rotation.y += dir.x * _cameraSpeed * DELTA;
		_rotation.x += dir.y * _cameraSpeed * DELTA;
	}

	_oldMousePos = mousePos;
	

	Transform::Update();

	XMVECTOR   eyePos = _translation;
	XMVECTOR focusPos = _translation + _forward;
	XMVECTOR upVector = _up;

	XMMATRIX matrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_view->SetMatrix(matrix, _srt);
	_view->SetVSBuffer(1);
}

void Camera::TargetMode()
{
	mouseDir.Normalize();
	dir = mouseDir;

	_rotation.y += mouseDir.x * _cameraSpeed * DELTA;
	_rotation.x += mouseDir.y * _cameraSpeed * DELTA;

	mouseDir.x = 0;
	mouseDir.y = 0;

	if (_rotation.x >= 2.0944f)
		_rotation.x = 2.0944f;
	else if (_rotation.x <= 0.785398f) //45
		_rotation.x = 0.785398f;
	
	XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, 0.0f);

	Vector3 forward = FORWARD_VECTOR * rotMatrix;
	
	Vector3 worldPos = _target->GetWorldPos();

	_translation = worldPos + UP_VECTOR * _targetHeight - _targetDistance * forward;

	Transform::Update();

	XMMATRIX matrix = XMMatrixLookAtLH(_translation, _target->_translation + _offset, UP_VECTOR);

	_view->SetMatrix(matrix, _srt);

	_view->SetVSBuffer(1);
}

void Camera::SetViewBuffer()
{
	XMVECTOR   eyePos = _translation;
	XMVECTOR focusPos = _translation + _forward;
	XMVECTOR upVector = _up;

	XMMATRIX matrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_view->SetMatrix(matrix, _srt);
	_view->SetVSBuffer(1);
}