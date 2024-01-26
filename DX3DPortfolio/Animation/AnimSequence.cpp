#include "framework.h"
#include "AnimSequence.h"

AnimSequence::AnimSequence(string actorName, string animName)
{
	ClipData data;

	data.savePath = "Actor/Model/Data/" + actorName + "/Clip/" + animName + ".clip";

	ModelReader::ReadClip(data);

	_animName = data.name;
	_duration = data.duration;
	_frameCount = data.frameCount;
	_keyTransforms = data.keyTransforms;
	_ticksPerSec = data.ticksPerSecond;
}

AnimSequence::~AnimSequence()
{
	_keyTransforms.clear();
}

void AnimSequence::Update(FrameBuffer::Data& frame)
{
	frame.cur.time += Time::Delta() * _ticksPerSec * frame.cur.speed;

	if (frame.cur.time >= 1.0f)
	{
		++frame.cur.curFrame %= (_frameCount - 1);
		frame.cur.nextFrame = (frame.cur.curFrame + 1) % (_frameCount);
		frame.cur.time = 0.0f;
		frame.next.speed = frame.cur.speed;
	}
}

void AnimSequence::UpdateNextFrame(FrameBuffer::Data& frame)
{
	frame.tweenTime += Time::Delta() / frame.takeTime;

	if (frame.tweenTime >= 1.0f)
	{
		frame.cur = frame.next;
		frame.tweenTime = 0.0f;

		frame.next.clipIndex = -1;
		frame.next.curFrame = 0;
		frame.next.nextFrame = 1;
		frame.next.time = 0.0f;
		frame.next.speed = 1.0f;
	}
	else
	{
		frame.next.time += Time::Delta() * _ticksPerSec * frame.next.speed;

		if (frame.next.time >= 1.0f)
		{
			++frame.next.curFrame %= _frameCount;
			frame.next.nextFrame = (frame.next.curFrame + 1) % _frameCount;
			frame.next.time = 0.0f;
		}
	}
}