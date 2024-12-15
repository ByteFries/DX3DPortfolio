#pragma once
class Observable
{
public:
	virtual ~Observable() {}

	virtual void RegisterObserver(Observer* observer) abstract;
	virtual void RemoveObserver(Observer* observer) abstract;
	virtual void NotifyObserver(Observer* observer) abstract;
	virtual void NotifyObservers() abstract;
};