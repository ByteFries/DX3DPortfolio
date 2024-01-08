#pragma once
class CameraManager : public Singleton<CameraManager>
{
	friend class Singleton;

	CameraManager();
	~CameraManager();
public:
	void Update();
	
	void Render();
	void Debug();

	Camera* GetMainCamera() { return _cameras[0]; }

	Camera* CreateCamera();

	static bool _hideCamera;
private:
	vector<Camera*> _cameras;
	ActorInstancing* _cameraInstance;
};