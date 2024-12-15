#pragma once
class Transform
{
public:
	Transform(string label = "Transform");
	virtual ~Transform();
	Transform(const Transform& transform);

	void Update();

	void SetWorld();
	void SetParent(Transform* parent) { _parent = parent; }

	XMMATRIX GetSRT() { return _srt; }

	Vector3 _scale = { 1.0f, 1.0f, 1.0f };
	Vector3 _rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 _translation = { 0.0f, 0.0f, 0.0f };
	Quaternion _qRotation;

	Vector3 ApplyingToVertex(Vector3 vertex);
	const Vector3& GetWorldPos() { return _worldTranslation; }
	const Vector3& GetWorldScale() { return _worldScale; }
	const Vector3& GetWorldRotation() { return _worldRotation; }
	const Quaternion& GetQuaternion() {return _qRotation; }

	Vector3	  Forward() { return _forward; }
	Vector3	 Backward() { return _forward * -1; }
	Vector3		Right() { return _right; }
	Vector3      Left() { return _right * -1; }
	Vector3		   Up() { return _up; }
	Vector3		 Down() { return _up * -1; }

	void SetLabel(string label) { _label = label; }
protected:
	WorldBuffer* _wBuffer;

	Vector3 _pivot = {};
	XMMATRIX _srt;
	Transform* _parent = nullptr;

	Vector3 _forward;
	Vector3 _up;
	Vector3 _right;

	Vector3 _worldScale = { 1,1,1 };
	Vector3 _worldRotation = { 0,0,0 };
	Vector3 _worldTranslation = { 0,0,0 };

	string _label = "";
};

