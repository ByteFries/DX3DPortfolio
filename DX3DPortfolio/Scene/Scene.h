#pragma once
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Update() abstract;

	virtual void PreRender() abstract;
	virtual void Render() abstract;
	virtual void PostRender() abstract;
	virtual void Debug() abstract;
};

