#include "framework.h"
#include "ModelClip.h"

ModelClip::ModelClip()
{
}

ModelClip::ModelClip(ClipData data)
{
	_name = data.name;
	_duration = data.duration;
	_frameCount = data.frameCount;
	_keyTransforms = data.keyTransforms;
	_ticksPerSec = data.ticksPerSecond;
}

ModelClip::~ModelClip()
{
	_keyTransforms.clear();
}

vector<KeyTransform> ModelClip::GetKeyTransforms(string name)
{
	if (_keyTransforms.count(name) == 0)
		return vector<KeyTransform>();
	
	return _keyTransforms[name];
}

void ModelClip::Update(FrameBuffer::Data& data)
{
	data.cur.time += Time::Delta() * _ticksPerSec * data.cur.speed;

	if (data.cur.time >= 1.0f)
	{
		++data.cur.curFrame %= (_frameCount - 1);
		data.cur.nextFrame = (data.cur.curFrame + 1) % (_frameCount);
		data.cur.time = 0.0f;
	}
}
