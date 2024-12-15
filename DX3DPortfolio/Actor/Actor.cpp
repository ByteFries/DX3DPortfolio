#include "framework.h"
#include "Actor.h"

Actor::Actor()
{
	_transform = new Transform();
}

Actor::~Actor()
{
	delete _transform;
}

void Actor::Update()
{
	_transform->Update();
}


void Actor::Debug()
{
}
