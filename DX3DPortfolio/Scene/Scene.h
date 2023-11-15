#pragma once
class Scene
{
public:
	virtual ~Scene() {}

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender() abstract;
};