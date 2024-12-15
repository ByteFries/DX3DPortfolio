#pragma once
class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update();
	void SetName(string name) { _name = name; }
	string GetName() { return _name; }

	Transform* GetTransform() { return _transform; }

	virtual void Debug();
protected:
	Transform* _transform;
	string _name;
};

