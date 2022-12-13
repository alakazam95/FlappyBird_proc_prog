#pragma once

#include "Timer.h"
#include "Object.h"
#include "Bird.h"
#include "Floor.h"
#include "ScrollTube.h"


struct GObject {
	Object* object;
	Object* clone;
};

class Game {

public:
	~Game();
	void initGame();
	void destroyGame();
	void run();
	bool isPaused();
	bool isStarted();

	static Game* getInstance();

private:
	Game();

	Timer gameTimer;
	Timer objectsTimer;
	const int FPS = 60;
	const int frameTime = 1000.0 / FPS;

	GObject bird;
	GObject floor;
	GObject scrollTube;


	bool paused;
	bool started;

	
	static Game* instance;

	void showPoints();
	void gameOver();


};