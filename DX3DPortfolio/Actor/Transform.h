#pragma once
class Transform
{
public:
	Transform(string lable = "Transform");
	virtual ~Transform();

	void Update();
	void Debug();

	void SetParent(Transform* parent) { _parent = parent; }

	XMMATRIX GetSRT() { return _srt; }

	Vector3 _scale = { 1.0f, 1.0f, 1.0f };
	Vector3 _rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 _translation = { 0.0f, 0.0f, 0.0f };

	const Vector3 GetWorldPos() { return _worldTranslation; }
	const Vector3 GetWorldScale() { return _worldScale; }
	const Vector3 GetWorldRotation() { return _worldRotation; }

	Vector3	  Forward() { return _forward; }
	Vector3	 Backward() { return _forward * -1; }
	Vector3		Right() { return _right; }
	Vector3      Left() { return _right * -1; }
	Vector3		   Up() { return _up; }
	Vector3		 Down() { return _up * -1; }

	void SetLabel(string label) { _label = label; }
protected:
	Vector3 _pivot = {};

	WorldBuffer* _wBuffer;
	XMMATRIX _srt;
	Transform* _parent = nullptr;

	Vector3 _forward;
	Vector3 _up;
	Vector3 _right;

	Vector3 _worldScale = { 1.0f, 1.0f, 1.0f };
	Vector3 _worldRotation = { 0.0f, 0.0f, 0.0f };
	Vector3 _worldTranslation = { 0.0f, 0.0f, 0.0f };

	string _label = "";

};

