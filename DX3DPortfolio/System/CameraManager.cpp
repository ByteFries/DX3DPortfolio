#include "framework.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
    Camera* camera = new Camera;
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
    for (Camera* c : _cameras)
        c->Update();
}

Camera* CameraManager::CreateCamera()
{
    Camera* camera = new Camera;

    _cameras.push_back(camera);

    return camera;
}