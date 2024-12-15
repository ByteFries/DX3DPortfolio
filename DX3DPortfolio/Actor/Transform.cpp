#include "framework.h"
#include "Transform.h"

Transform::Transform(string label)
	:_label(label)
{
	_wBuffer = new WorldBuffer();
}

Transform::~Transform()
{
	delete _wBuffer;
}

Transform::Transform(const Transform& transform)
{
	_scale = transform._scale;
	_rotation = transform._rotation;
	_translation = transform._translation;
	_qRotation = transform._qRotation;

	_wBuffer = new WorldBuffer();
;	_srt = transform._srt;
	_pivot = transform._pivot;

	_forward = transform._forward;
	_up = transform._up;
	_right = transform._right;

	_worldScale = transform._worldScale;
	_worldRotation = transform._worldRotation;
	_worldTranslation = transform._worldTranslation;
}

void Transform::Update()
{

	_qRotation = XMQuaternionRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	//XMVECTOR tmp = XMQuaternionRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	//float x = XMVectorGetX(tmp);
	//float y = XMVectorGetY(tmp);
	//float z = XMVectorGetZ(tmp);
	//float w = XMVectorGetW(tmp);


	_srt = XMMatrixTransformation
	(
		_pivot,
		XMQuaternionIdentity(),
		_scale,
		_pivot,
		_qRotation,
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

void Transform::SetWorld()
{
	_wBuffer->SetVSBuffer(0);
}

Vector3 Transform::ApplyingToVertex(Vector3 vertex)
{
	XMVECTOR localPos = { vertex.x, vertex.y, vertex.z, 1 };
	XMVECTOR worldPos = XMVector3Transform(localPos, _srt);
	return worldPos;
}
