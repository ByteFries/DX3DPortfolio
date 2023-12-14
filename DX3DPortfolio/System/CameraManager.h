#pragma once
class CameraManager : public Singleton<CameraManager>
{
	friend class Singleton;

	CameraManager();
	~CameraManager();
public:
	void Update();
	
	Camera* GetMainCamera() { return _cameras[0]; }

	Camera* CreateCamera();
private:
	vector<Camera*> _cameras;
};

