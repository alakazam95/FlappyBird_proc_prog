#pragma once

#include <ctime>

class Timer {
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	unsigned int getTicks();

	bool ifStart();
	bool ifPause();
	bool ifStop();

private:
	clock_t startTicks;
	clock_t pausedTicks;
	bool started;
	bool paused;
};