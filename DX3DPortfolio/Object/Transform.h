#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	void Update();

	void SetParent(Transform* parent) { _parent = parent; }

	XMMATRIX GetSRT() { return _srt; }

	Vector3 _scale = { 1.0f, 1.0f, 1.0f };
	Vector3 _rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 _translation = { 0.0f, 0.0f, 0.0f };

	const Vector3 GetWorldPos() { return _worldScale; }
protected:
	Vector3 _pivot = {};

	MatrixBuffer* _mBuffer;
	XMMATRIX _srt;
	Transform* _parent;

	Vector3 _forward;
	Vector3 _up;
	Vector3 _right;

	Vector3 _worldScale = { 1.0f, 1.0f, 1.0f };
	Vector3 _worldRotation = { 0.0f, 0.0f, 0.0f };
	Vector3 _worldTranslation = { 0.0f, 0.0f, 0.0f };

};

