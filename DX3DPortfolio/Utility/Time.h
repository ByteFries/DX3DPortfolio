#pragma once
class Time : public Singleton<Time>
{
	friend class Singleton;
	Time();
	~Time();
public:
	void Update();

	static float Delta() { return _timeElapsed; }
	static float PhysicsTick() { return _physicsTick; }
	float RunningTime() { return _runningTime; }

	UINT GetFPS() { return _frameRate; }

	void LockFPS(float val) { _scanningRate = val; }
	void Debug();
private:
	static float _timeElapsed;
	static float _physicsTick;

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

