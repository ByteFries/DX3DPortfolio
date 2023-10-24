#include "Framework.h"
#include "Time.h"

float Time::_timeElapsed = 0.0;

Time::Time()
	: _curTick(0), _frameCount(0), _frameRate(0), _oneSecCount(0), _runningTime(0), _scanningRate(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&_ticksPerSecond);

	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTick);

	_timeScale = 1.0 / _ticksPerSecond;
}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTick);

	_timeElapsed = (_curTick - _lastTick) * _timeScale;

	if (_scanningRate != 0)
	{
		while (_timeElapsed < (1.0 / _scanningRate))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTick);
			_timeElapsed = (_curTick - _lastTick) * _timeScale;
		}
	}

	_lastTick = _curTick;

	_frameCount++;

	_oneSecCount += _timeElapsed;

	_runningTime += _timeElapsed;

	if (_oneSecCount >= 1.0)
	{
		_frameRate = _frameCount;
		_frameCount = 0;

		_oneSecCount = 0;
	}
}