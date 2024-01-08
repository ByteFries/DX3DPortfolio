#include "framework.h"
#include "CameraManager.h"

bool CameraManager::_hideCamera = true;

CameraManager::CameraManager()
{
    _cameraInstance = new ActorInstancing("Camera");

    Camera* camera = new Camera;
    camera->SetCameraMode(Camera::CameraMode::FREE);
    camera->SetLabel("MainCamera");
    _cameras.push_back(camera);

    _cameraInstance->Add(Vector3(0,0,0), camera);
    _cameraInstance->GetDatas()[0].isActive = false;
}

CameraManager::~CameraManager()
{
    for (Camera* c : _cameras)
        delete c;

    _cameras.clear();

    delete _cameraInstance;
}

void CameraManager::Update()
{
    vector<ActorInstancing::Data>&  datas = _cameraInstance->GetDatas();

    for (int i = 0; i < _cameras.size(); i++)
    {
        _cameras[i]->Update();
        datas[i].transform = _cameras[i];
    }

    if (_hideCamera)
        return;

    _cameraInstance->Update();
}

void CameraManager::Render()
{
    if (_hideCamera)
        return;

    _cameraInstance->Render();
}

void CameraManager::Debug()
{
    for (Camera* camera : _cameras)
        camera->Debug();
}

Camera* CameraManager::CreateCamera()
{
    Camera* camera = new Camera;

    _cameras.push_back(camera);

    _cameraInstance->Add(Vector3(0,0,0), camera);

    return camera;
}