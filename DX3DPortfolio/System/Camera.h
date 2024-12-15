#pragma once
class Camera : public Transform
{
	friend class CameraManager;
	Camera();
	~Camera();
public:
	enum CameraMode
	{
		FREE,
		TARGET,
		STATIC
	};

	void Update();

	void SetTarget(Transform* target) { _target = target; }

	void SetView();

	void SetVSBuffer(UINT slot);

	void SetLabel(string label) { _label = label; }

	void SetCameraMode(CameraMode mod) { _cameraMode = mod; }

	void Debug();
private:
	void FreeMode();
	void TargetMode();
	void StaticMode();

	void SetViewBuffer();

	bool _lock = false;

	Transform* _target;
	float _targetDistance = 25.0f;
	float _targetHeight = 20.0f;
	Vector3 _offset = UP_VECTOR * 2.0f;

	CameraBuffer* _cBuffer;

	Vector3 _oldMousePos;

	float _moveSpeed = 10.0f;
	float _rotSpeed = 2.5f;

	Vector3 _dir;

	string _label;

	CameraMode _cameraMode = STATIC;
};

