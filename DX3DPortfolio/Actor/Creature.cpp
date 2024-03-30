#include "framework.h"
#include "Creature.h"

Creature::Creature(string name)
	:Actor(name)
{
}

Creature::~Creature()
{
	delete _animManager;
}

void Creature::Update()
{
	Actor::Update();


	if (!_animManager)
		return;

	_animManager->Update();
}

void Creature::Render()
{
	if (_animManager)
	{
		_animManager->SetSubResources();
		_wBuffer->SetAnimation(true);

	}
	else
		_wBuffer->SetAnimation(false);

	Actor::Render();
}

void Creature::PlayClip(State state, float speed, float takeTime)
{
	if (!_animManager)
		return;

	_animManager->PlaySequence(state, speed, takeTime);
}