
#include "Object.h"

#include <conio.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>

#include "Timer.h"
#include "Console.h"

#include "Bird.h"
#include "Floor.h"

#include "Game.h"
#include "Tube.h"
#include "ScrollTube.h"
#include "Menu.h"
#include "Logo.h"

using namespace std;

static void showLogo() {
	Console::showString("by alakazam, chechen games", 49, 6, 12);
}

int main() {
	
	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	//Console::setWindowSize(850, 450);
	Console::setWindowSize(850, 500);
	Console::showConsoleCursor(false);

	
	Game* game = Game::getInstance();
	//game.initGame();
	//game.run();
	

	//menu

	Logo logo(Position(13, 0), "logo.txt", 1);
	Logo* clogo = (Logo*)logo.clone();
	logo.draw();

	showLogo();


	Menu menu(Position(36, 12));
	menu.show();

	Timer logoTimer;
	logoTimer.start();

	while (true) {

		logo.update(logoTimer.getTicks());
		if (logo.checkStateChanged()) {
			clogo->clear();
			delete clogo;
			clogo = (Logo*)logo.clone();
			logo.draw();
		}

		if (_kbhit()) {
			char button = _getch();
			switch (button) {
				case 72: --menu; break;
				case 80: ++menu; break;
				case 13: menu.doAction(); system("cls"); showLogo(); break;
			}
			menu.show();
		}

	}



	_getch();

	return 0; 
	
}
