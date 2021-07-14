#include <chrono>
#include "Animation.h"

Animation::Animation(unsigned int duration)
{
	_duration = duration;
}

void Animation::onStart(std::function<void()> callback)
{
	_onStart = callback;
}

void Animation::onLoop(std::function<void(float progress)> callback)
{
	_onLoop = callback;
}

void Animation::onDone(std::function<void()> callback)
{
	_onDone = callback;
}

void Animation::onInterval(unsigned int interval, std::function<void()> callback, bool lazy)
{
	_onInterval = callback;
	_interval = interval;
	_lazy_interval = lazy;
}

void Animation::start()
{
	_startingTime = std::chrono::steady_clock::now();
	_interval_count = 0;
	if (!_isRunning)
	{
		_isRunning = true;
		if (_onStart)
			_onStart();
	}
}

void Animation::loop()
{
	using namespace std::chrono;
	if (_isRunning)
	{
		_iteration = duration_cast<milliseconds>((steady_clock::now() - _startingTime)).count();

		if (_interval > 0)
		{
			unsigned int available_intervals = _iteration / _interval;
			if (available_intervals > _interval_count)
			{
				if (_lazy_interval)
				{
					_onInterval();
				}
				else
				{
					for (size_t i = 0; i < (available_intervals - _interval_count); i++)
					{
						_onInterval();
					}
				}
				_interval_count = available_intervals;
			}
		}

		if (_iteration >= _duration)
		{
			stop();
		}
		else
		{
			if (_onLoop)
				_onLoop((float)_iteration / _duration);
		}
	}
}

void Animation::stop()
{
	_isRunning = false;
	_interval_count = 0;
	if (_onDone)
		_onDone();
}

bool Animation::isRunning()
{
	return _isRunning;
}