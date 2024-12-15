#include "framework.h"
#include "Light.h"

Light::Light(Data* data, int index, string name)
	:_data(data), _index(index), _name(name)
{
	RegisterObserver(LightManager::Get());
	_transform = new Transform;
}

Light::~Light()
{
	_observers.clear();
	delete _transform;
}

void Light::Update()
{
	_transform->Update();
	_data->position = _transform->GetWorldPos();
	_data->direction = _transform->_rotation;
}

void Light::Debug()
{
	if (ImGui::TreeNode(_name.c_str()))
	{
        bool changed = false;

        const char* lightTypeNames[] = { "Point Light", "Directional Light", "Spot Light", "Capsule Light" };

        if (ImGui::Combo("Light Type", (int*)&_data->type, lightTypeNames, IM_ARRAYSIZE(lightTypeNames)))
        {
            changed = true;
        }

        switch (_data->type)
        {
        case DIRECTIONAL_LIGHT:
            break;
        case POINT_LIGHT:
            break;
        case SPOT_LIGHT:
            break;
        case CAPSULE_LIGHT:
            break;
        default:
            break;
        }

        bool checked = _data->active != 0;
        if (ImGui::Checkbox("Active", &checked))
        {
            _data->active = checked;
            changed = true;
        }

        float* color = reinterpret_cast<float*>(&_data->color);
        if (ImGui::ColorEdit4("LightColor", color))
        {
            changed = true;
        }

        if (ImGui::InputFloat3("Direction", &_transform->_rotation.x))
        {
            changed = true;
        }

        if (ImGui::InputFloat3("Position", &_transform->_translation.x))
        {
            changed = true;
        }

        if (changed)
        {
            NotifyObservers();
        }

        ImGui::TreePop();
	}
}

void Light::SetType(LightType type)
{
	_data->type = type;
}

void Light::RegisterObserver(Observer* observer)
{
	_observers.push_back(observer);
}

void Light::RemoveObserver(Observer* observer)
{
	auto it = std::remove(_observers.begin(), _observers.end(), observer);

	if (it != _observers.end()) 
	{
		_observers.erase(it, _observers.end());
	}
}

void Light::NotifyObserver(Observer* observer)
{
	observer->UpdateObserver();
}

void Light::NotifyObservers()
{
	for (Observer* observer : _observers)
		observer->UpdateObserver();
}
