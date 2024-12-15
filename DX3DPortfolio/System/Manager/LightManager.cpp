#include "framework.h"
#include "LightManager.h"

LightManager::LightManager()
{
    _lBuffer = new LightBuffer();
}

LightManager::~LightManager()
{
    delete _lBuffer;
}


Light* LightManager::CreateLight()
{
    if (_lBuffer->data.lightCount >= MAX_LIGHT) //�ִ� ����Ʈ ���� �ʰ�
        return nullptr;
    int index = _lBuffer->data.lightCount;
    Data& lightData = _lBuffer->data.lights[_lBuffer->data.lightCount++];
    Light* light = new Light(&lightData, index);
    return light;
}

Data* LightManager::GetLightData(int index)
{
    if (index < 0 || index >= _lBuffer->data.lightCount) //�ε��� ��ȿ�� �˻�
        return nullptr;

    return &_lBuffer->data.lights[index];
}

void LightManager::SetLight()
{
    _lBuffer->SetPSBuffer(0);
}

void LightManager::Update()
{
    if (_needToUpdate)
    {
        _lBuffer->UpdateSubresource();
    }
}

void LightManager::UpdateObserver()
{
    _needToUpdate = true;
}
