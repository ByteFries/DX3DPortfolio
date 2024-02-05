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
	if (_animManager->CanUse())
	{
		_animManager->SetSubResources();
		_wBuffer->SetAnimation(true);

	}
	else
		_wBuffer->SetAnimation(false);

	_wBuffer->SetVSBuffer(0);


	_mesh->Render();
}

void Actor::Update()
{
	Transform::Update();

	if (!_animManager)
		return;

	_animManager->Update();
}

void Actor::Debug()
{
	//for (ModelPart* part : _parts)
	//{
	//	part->GetMaterial()->Debug();
	//}
}

void Actor::PlayClip(State state, float speed, float takeTime)
{
	if (!_animManager)
		return;

	_animManager->PlaySequence(state, speed, takeTime);
}