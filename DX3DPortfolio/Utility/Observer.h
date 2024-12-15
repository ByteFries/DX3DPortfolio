#pragma once
class Observer
{
public:
	virtual ~Observer() {}
	virtual void UpdateObserver() abstract;
};