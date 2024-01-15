#include "framework.h"
#include "BlendSpace.h"

BlendSpace::BlendSpace(string actorName)
	:_actorName(actorName)
{
}

BlendSpace::~BlendSpace()
{
	for (int i = 0; i < _sequences.size(); i++)
	{
		for (int j = 0; j < _sequences[i].size(); j++)
			delete _sequences[i][j];
	}
}

void BlendSpace::Update(int speed, int direction)
{
	int speedIndex = _maxSpeed / speed / _sequences.size();
	int dirIndex = direction / (360 / _sequences[speedIndex].size());

	//tweening
}

void BlendSpace::AddAnimation(string animName, int speed, int direction)
{
	AnimSequence* sequence = new AnimSequence(_actorName, animName);

	//_sequences[_maxSpeed / speed][];
}