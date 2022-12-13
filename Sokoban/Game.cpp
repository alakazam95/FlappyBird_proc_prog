#include "Game.h"

Game::Game() {
	bird.object = NULL;
	bird.clone = NULL;

	floor.object = NULL;
	floor.clone = NULL;

	scrollTube.object = NULL;
	scrollTube.clone = NULL;
}

Game::~Game() {
	destroyGame();
	if (instance != NULL) delete instance;
}

void Game::initGame() {

	destroyGame();

	bird.object = new Bird(Position(37, 12), "bird2.txt", 3);
	bird.clone = bird.object->clone();

	floor.object = new Floor(Position(0, 23), "floor.txt", 2);

	scrollTube.object = new ScrollTube((Bird*)bird.object);
	scrollTube.clone = scrollTube.object->clone();


}

void Game::destroyGame() {
	if (bird.object) delete bird.object;
	if (bird.clone) delete bird.clone;

	if (floor.object) delete floor.object;
	if (floor.clone) delete floor.clone;

	if (scrollTube.object) delete scrollTube.object;
	if (scrollTube.clone) delete scrollTube.clone;

	scrollTube.object = NULL;
	scrollTube.clone = NULL;

	bird.object = NULL;
	bird.clone = NULL;

	floor.object = NULL;
	floor.object = NULL;
}

bool Game::isPaused() {
	return paused;
}

bool Game::isStarted() {
	return started;
}

void Game::run() {


	objectsTimer.start();

	floor.object->draw();

	bool gameover = false;

	while (!gameover) {

		gameTimer.start();

		if (_kbhit()) {
			char button = _getch();
			switch (button) {
			case 27: gameover = true; break;
			case 'w': bird.object->up(); break;
			case 's': bird.object->down(); break;
			case 'a': bird.object->left(); ((Bird*)bird.object)->turnLeft(); break;
			case 'd': bird.object->right(); ((Bird*)bird.object)->turnRight(); break;
			case 'o': ((ScrollTube*)scrollTube.object)->startScroll(); break;
			case 'p': ((ScrollTube*)scrollTube.object)->stopScroll();  break;
			case 32:  ((Bird*)bird.object)->jump(); ((ScrollTube*)scrollTube.object)->startScroll(); break;

			}
			if (button >= '1' && button <= '9') {
				scrollTube.object->setColor(button - '0');
			}
		}

		//collisions
		if (bird.object->collision(*floor.object)) {
			gameOver();
			return;
		}

		if (scrollTube.object->collision(*bird.object)) {
			gameOver();
			return;
		}
		//////


		((ComplexObject*)bird.object)->update(objectsTimer.getTicks());
		if (bird.object->checkStateChanged()) {
			bird.clone->clear();
			delete bird.clone;
			bird.clone = bird.object->clone();
			bird.object->draw();
		}

		((ComplexObject*)scrollTube.object)->update(objectsTimer.getTicks());
		if (scrollTube.object->checkStateChanged()) {
			scrollTube.object->draw();
			//floor.object->draw();
		}

		//show points
		showPoints();


		
		int timeEnd = gameTimer.getTicks();
		if (timeEnd < frameTime) {
			Sleep(frameTime - timeEnd);
		}


	}
}

void Game::showPoints() {

	const int x = 1;
	const int y = 26;

	static int lastPoints = -1;
	int points = ((Bird*)bird.object)->getPoints();
	if (points != lastPoints) {
		Console::clearString(x, y, 20);
		Console::showString("Halhatar: ", x, y, 12);
		Console::showString(std::to_string(points), x + 8, y, 15);
		lastPoints = points;
	}
}

void Game::gameOver() {
	for (int i = 0; i < 3; ++i) {
		bird.object->clear();
		Sleep(50);
		bird.object->draw();
		Sleep(50);
	}
	const int x = 18;
	const int y = 26;
	const int color = 15;
	std::string message = "Ho eshan, hayn luarg nuiyd tIetaIe korta menu chu Iar val";
	for (int i = 0; i < message.size(); ++i) {
		Console::draw_force(x + i, y, color, message[i]);
		Sleep(10);
	}
	_getch();
}

Game* Game::instance = NULL;

Game* Game::getInstance() {
	if (instance == NULL) instance = new Game();
	return instance;
}