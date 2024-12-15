#include "framework.h"
#include "Camera.h"

Camera::Camera()
{
	_cBuffer = new CameraBuffer();
}

Camera::~Camera()
{
	delete _cBuffer;
}

void Camera::Update()
{
	switch (_cameraMode)
	{
	case FREE:
		FreeMode();
		break;
	case TARGET:
		TargetMode();
		break;
	case STATIC:
		StaticMode();
		break;
	default:
		break;
	}
}
void Camera::SetView()
{
	Transform::Update();

	XMMATRIX viewMatrix = XMMatrixInverse(nullptr, _srt);

	_cBuffer->SetMatrix(viewMatrix, _srt);
	_cBuffer->SetVSBuffer(1);
}

void Camera::SetVSBuffer(UINT slot)
{
	_cBuffer->SetVSBuffer(slot);
}


void Camera::Debug()
{

}

void Camera::FreeMode()
{
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		if (KEY_DOWN('Z'))
			_lock = !_lock;
		if (!_lock)
		{
			if (KEY_PRESS('W'))
			{
				_translation += DELTA * _moveSpeed * _forward;
			}
			if (KEY_PRESS('S'))
			{
				_translation += DELTA * _moveSpeed * -1 * _forward;
			}
			if (KEY_PRESS('A'))
			{
				_translation += DELTA * _moveSpeed * -1 * _right;
			}
			if (KEY_PRESS('D'))
			{
				_translation += DELTA * _moveSpeed * _right;
			}
			if (KEY_PRESS('Q'))
			{
				_translation.y += DELTA * _moveSpeed;
			}
			if (KEY_PRESS('E'))
			{
				_translation.y -= DELTA * _moveSpeed;
			}
		}

		if (KEY_PRESS(VK_LBUTTON))
		{
			Vector3 dir = (mousePos - _oldMousePos).GetNormalized();

			_rotation.y += dir.x * _rotSpeed * DELTA;
			_rotation.x += dir.y * _rotSpeed * DELTA;
		}
	}
	
	_oldMousePos = mousePos;

	Transform::Update();

	XMMATRIX matrix = XMMatrixInverse(nullptr, _srt);

	_cBuffer->SetMatrix(matrix, _srt);
	_cBuffer->SetVSBuffer(1);
}

void Camera::TargetMode()
{
}

void Camera::StaticMode()
{
}

void Camera::SetViewBuffer()
{
	XMVECTOR   eyePos = _translation;
	XMVECTOR focusPos = _translation + _forward;
	XMVECTOR upVector = _up;

	XMMATRIX matrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_cBuffer->SetMatrix(matrix, _srt);
	_cBuffer->SetVSBuffer(1);
}
