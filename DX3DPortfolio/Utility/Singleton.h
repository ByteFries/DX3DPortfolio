#pragma once
template<class T>
class Singleton
{
public:
	virtual ~Singleton<T>() {}
	static T* Get();
	static void Delete();

protected:
	static T* _instance;

};

template<class T>
T* Singleton<T>::_instance = nullptr;

template<class T>
inline T* Singleton<T>::Get()
{
	if (_instance == nullptr)
		_instance = new T();

	return _instance;
}

template<class T>
inline void Singleton<T>::Delete()
{
	if (_instance != nullptr)
		delete _instance;
}
