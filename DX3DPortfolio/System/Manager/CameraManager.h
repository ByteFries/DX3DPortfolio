#pragma once
class CameraManager : public Singleton<CameraManager>
{
	friend class Singleton;
	CameraManager();
	~CameraManager();
public:
	void Update();

	void Render();

	Camera* GetMainCamera() { return _cameras[0]; }

	Camera* CreateCamera();

	static bool _hidCameras;
private:
	vector<Camera*> _cameras;
};

