#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
	_mBuffer = new MatrixBuffer();
}

Transform::~Transform()
{
	delete _mBuffer;
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
