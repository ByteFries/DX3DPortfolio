#pragma once

class Camera :public Transform
{
	friend class CameraManager;
	Camera();
	~Camera();
public:
	void Update();

	Ray ScreenPointToRay(Vector3 pos);

	void SetTarget(Transform* transform) { _target = transform; }

	void SetView();

	void SetVSBuffer(UINT slot);

	void Debug();
private:
	void FreeMode();
	void TargetMode();

	void SetViewBuffer();
	
	Transform* _target;
	float _targetDistance = 25.0f;
	float _targetHeight = 20.0f;
	Vector3 _offset = UP_VECTOR * 2.0f;
	CameraBuffer* _view;

	Vector3 _oldMousePos;

	float _cameraSpeed = 2.0f;

	Vector3 dir;
};