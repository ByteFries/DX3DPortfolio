#include "framework.h"
#include "Animation/AnimManager.h"
#include "Actor.h"

Actor::Actor(string name)
	:_name(name)
{
}

Actor::~Actor()
{
}

void Actor::Render()
{
	_wBuffer->SetVSBuffer(0);

	_mesh->Render();
}

void Actor::Update()
{
	Transform::Update();

}

void Actor::Debug()
{
	//for (ModelPart* part : _parts)
	//{
	//	part->GetMaterial()->Debug();
	//}
}
