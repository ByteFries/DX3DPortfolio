#pragma once
class Camera :public Singleton<Camera>
{
	friend class Singleton;
	Camera();
	~Camera();
public:
	void Update();

	void Debug();
private:
	void FreeMode();
	void TargetMode();

	void SetView();
	
	MatrixBuffer* _view;

	Transform* _transform;

	Vector3 _oldMousePos;

	float _cameraSpeed = 10.0f;
};