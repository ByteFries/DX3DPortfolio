#include "framework.h"
#include "Animation/AnimManager.h"
#include "Actor.h"

Actor::Actor(string name)
	:_name(name)
{
}

Actor::~Actor()
{
	delete _mesh;
	delete _animManager;
}

void Actor::Render()
{
	_wBuffer->SetVSBuffer(0);

	if (_animManager)
	{
		_animManager->SetSubResources();
	}

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

void Actor::AddClip(string animName, float speed, float direction)
{
	if (!_animManager)
	{
		SkeletalMesh* mesh = dynamic_cast<SkeletalMesh*>(_mesh);

		if (mesh)
		{
			_animManager = new AnimManager(mesh);
			_wBuffer->SetAnimation(true);
		}
		else
			return;
	}

	_animManager->AddAnimation(_name, animName, speed, direction);
}

void Actor::PlayClip(State state, float speed, float takeTime)
{
	if (!_animManager)
		return;

	_animManager->PlaySequence(state, speed, takeTime);
}