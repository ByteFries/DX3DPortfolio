#pragma once
using namespace LightData;

class Light : public Observable
{
	friend class LightManager;
	Light(Data* data, int index, string name = "Light");
public:
	~Light();

	void Update();
	void Debug();

	int GetIndex() { return _index; }
	Transform* GetTransform() { return _transform; }

	void SetName(string name) { _name = name; }
	void SetType(LightType type);

	void RegisterObserver(Observer* observer) override;
	void RemoveObserver(Observer* observer) override;
	void NotifyObserver(Observer* observer) override;
	void NotifyObservers() override;
private:
	vector<Observer*> _observers;

	Transform* _transform;
	Data* _data;
	int _index;

	string _name = "Light";
};

