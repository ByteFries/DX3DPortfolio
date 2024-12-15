#pragma once
using namespace LightData;

class LightManager : public Singleton<LightManager>, Observer
{
	friend class Singleton;
	friend class Light;
	LightManager();
	~LightManager();
public:
	void SetLight();
	void Update();
	void UpdateObserver() override;

	Light* CreateLight();
	Data* GetLightData(int index);
private:
	

	LightBuffer* _lBuffer;
	bool _needToUpdate = false;

};