#pragma once
class AnimSequence
{
public:
	AnimSequence(string actorName, string animName);
	~AnimSequence();

	void Update(FrameBuffer::Data& frame);
	void UpdateNextFrame(FrameBuffer::Data& frame);

	const UINT GetFrameCount() { return _frameCount; }
	float GetTicksPerSec() { return _ticksPerSec; }
	float GetDuration() { return _duration; }

	vector<KeyTransform> GetKeyTransforms(string key) { return _keyTransforms[key]; }

private:
	string _animName;
	UINT _frameCount = 0;
	float _ticksPerSec = 0.0f;
	float _duration = 0.0f;

	unordered_map<string, vector<KeyTransform>> _keyTransforms = {};
};

