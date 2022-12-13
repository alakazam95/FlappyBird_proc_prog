#include "Timer.h"

Timer::Timer() {
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start() {
	started = true;
	paused = false;
	startTicks = clock();
	pausedTicks = 0;
}

void Timer::stop() {
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::pause() {
	if (started && !paused) {
		paused = true;
		pausedTicks = clock() - startTicks;
		startTicks = 0;
	}
}

void Timer::unpause() {
	if (started && paused) {
		paused = false;
		startTicks = clock() - pausedTicks;
		pausedTicks = 0;
	}
}

/* return the number of milliseconds which elapsed */
unsigned int Timer::getTicks() {
	clock_t time = 0;
	if (paused) time = pausedTicks;
	else time = clock() - startTicks;

	double mstime = (time / (double)CLOCKS_PER_SEC)*1000;
	return (unsigned int)mstime;
}

bool Timer::ifStart() {
	return started;
}

bool Timer::ifPause() {
	return paused;
}

bool Timer::ifStop() {
	return !started && !paused;
}