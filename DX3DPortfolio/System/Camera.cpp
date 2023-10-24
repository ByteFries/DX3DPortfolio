#include "framework.h"
#include "Camera.h"

Camera::Camera()
{
	_view = new MatrixBuffer();
	_transform = new Transform();
}

Camera::~Camera()
{
	delete _view;
	delete _transform;
}

void Camera::Update()
{
	FreeMode();
}

void Camera::Debug()
{
}

void Camera::FreeMode()
{
	if (KEY_PRESS('W'))
	{
		_transform->_translation += DELTA * _cameraSpeed * _transform->Forward();
	}
	if (KEY_PRESS('S'))
	{
		_transform->_translation += DELTA * _cameraSpeed * _transform->Backward();
	}
	if (KEY_PRESS('A'))
	{
		_transform->_translation += DELTA * _cameraSpeed * _transform->Left();
	}
	if (KEY_PRESS('D'))
	{
		_transform->_translation += DELTA * _cameraSpeed * _transform->Right();
	}
	if (KEY_PRESS('Q'))
	{
		_transform->_translation.y += DELTA * _cameraSpeed;
	}
	if (KEY_PRESS('E'))
	{
		_transform->_translation.y -= DELTA * _cameraSpeed;
	}

	if (KEY_PRESS(VK_LBUTTON))
	{
		Vector3 dir = (mousePos - _oldMousePos).GetNormalized();

		_transform->_rotation.y += dir.x * _cameraSpeed * DELTA;
		_transform->_rotation.x += dir.y * _cameraSpeed * DELTA;
	}

	_oldMousePos = mousePos;
	

	_transform->Update();
	SetView();
}

void Camera::TargetMode()
{
}

void Camera::SetView()
{
	XMVECTOR   eyePos = _transform->_translation;
	XMVECTOR focusPos = _transform->_translation + _transform->Forward();
	XMVECTOR upVector = _transform->Up();

	XMMATRIX matrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_view->SetMatrix(matrix);
	_view->SetVSBuffer(1);
}
