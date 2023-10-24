#pragma once
class Time : public Singleton<Time>
{
	friend class Singleton;
	Time();
	~Time();
public:
	void Update();

	static float Delta() { return _timeElapsed; }

	UINT GetFPS() { return _frameRate; }
private:
	static float _timeElapsed;

	INT64		_curTick;
	INT64		_lastTick;
	INT64 _ticksPerSecond;

	UINT  _frameRate;
	UINT _frameCount;

	float    _timeScale;
	float  _runningTime;
	float _scanningRate;
	float  _oneSecCount;
};

