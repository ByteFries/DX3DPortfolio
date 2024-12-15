#include "framework.h"
#include "CameraManager.h"

bool CameraManager::_hidCameras = true;

CameraManager::CameraManager()
{
    Camera* camera = new Camera;
    camera->SetCameraMode(Camera::FREE);
    _cameras.push_back(camera);
}

CameraManager::~CameraManager()
{
    for (Camera* c : _cameras)
        delete c;

    _cameras.clear();
}

void CameraManager::Update()
{
    for (int i = 0; i < _cameras.size(); i++)
    {
        _cameras[i]->Update();
    }
}

void CameraManager::Render()
{
}

Camera* CameraManager::CreateCamera()
{
    Camera* camera = new Camera;

    _cameras.push_back(camera);

    return camera;
}
