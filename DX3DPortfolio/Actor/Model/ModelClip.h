#pragma once
class ModelClip
{
public:
	ModelClip();
	ModelClip(ClipData data);
	~ModelClip();

	KeyFrame* GetKeyFrames(string name);

	void Update(FrameBuffer::Data& data);

	const string GetName() { return _name; }
	const UINT GetFrameCount() { return _frameCount; }
	float GetTicksPerSec() { return _ticksPerSec; }
	float GetDuration() { return _duration; }
private:
	string _name = "";
	UINT _frameCount = 0;
	float _ticksPerSec = 0.0f;
	float _duration = 0.0f;

	unordered_map<string, KeyFrame*> _keyFrames = {};
};

