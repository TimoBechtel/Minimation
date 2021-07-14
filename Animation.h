#pragma once

#include <functional>

class Animation
{
private:
	bool _isRunning = false;
	std::chrono::steady_clock::time_point _startingTime;
	uint64_t _iteration;
	unsigned int _duration;
	unsigned int _interval;
	unsigned int _interval_count;
	bool _lazy_interval;
	std::function<void()> _onStart;
	std::function<void(float progress)> _onLoop;
	std::function<void()> _onDone;
	std::function<void()> _onInterval;

public:
	Animation(unsigned int duration);
	void onStart(std::function<void()>);

	// Callback runs on every loop.
	// progress will be between 0.0 and 1.0
	void onLoop(std::function<void(float progress)>);
	void onDone(std::function<void()>);

	// The given function is called in the given interval.
	// Setting lazy to true (default) will ignore skipped function calls,
	// whereas setting it to false will stack callbacks.
	// This might be useful, if a loop takes longer than the given interval.
	void onInterval(unsigned int interval, std::function<void()> callback, bool lazy = true);

	// Call this in a loop.
	void loop();

	// Starts the animation.
	// It can also be used to reset the animation.
	void start();
	void stop();
	bool isRunning();
};
