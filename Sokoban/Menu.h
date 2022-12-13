#pragma once

#include <iostream>
#include <vector>
#include "Position.h"
#include "Console.h"
#include <string>
#include "Game.h"

struct Option {
	std::string name;
	void* (*action)();
	int color;

	Option(std::string nname, int ccolor) {
		name = nname;
		color = ccolor;
	}

};

//actions
static void* testAction() {

	
	return NULL;
}

static void* newGameAction() {

	system("cls");
	const int color = 11;
	std::string message = "Space - khoslar";
	for (int i = 0; i < message.length(); ++i) {
		Console::draw(i + 1, 2, color, message[i]);
		Sleep(10);
	}
	Game* game = Game::getInstance();
	game->initGame();
	game->run();


	return NULL;
}

static void* endGameAction() {
	exit(0);
}

static void* authors() {
	system("cls");
	std::cout << "Authors:" << std::endl << std::endl;
	std::cout << "alakazam and nohchi vezhri" << std::endl;
	std::cout << "IMBO-01-22" << std::endl;
	std::cout << "RTU MIREA" << std::endl;
	std::cout << "Hayn luarg nuiyd tIetaIe korta menu chu Iar val" << std::endl << std::endl;
	_getch();
	return NULL;
}

static void* controlHelpAction() {
	system("cls");
	std::cout << "Urhalla" << std::endl << std::endl;
	std::cout << "enter - niys darh" << std::endl;
	std::cout << "lakha lowha nuids tIetaIe" << std::endl;
	std::cout << "space - khoslor" << std::endl << std::endl;
	std::cout << "Hayn luarg nuiyd tIetaIe korta menu chu Iar val" << std::endl;
	_getch();
	return NULL;
}

class Menu {
public:
	Menu(Position position) {
		this->position = position;
		optionPtr = 0;
		
		options.push_back(Option("Kel lovzar", hoverColor)); options[0].action = newGameAction;
		//options.push_back(Option("Kontynuuj", linkColor)); options[1].action = testAction;
		//options.push_back(Option("Najlepsze wyniki", linkColor)); options[2].action = testAction;
		options.push_back(Option("Urhalla", linkColor)); options[1].action = controlHelpAction;
		options.push_back(Option("Kholarho", linkColor)); options[2].action = authors;
		options.push_back(Option("Iar val", linkColor)); options[3].action = endGameAction;

	}

	void operator++() {
		options[optionPtr].color = linkColor;
		if (optionPtr < options.size() - 1) ++optionPtr;
		else optionPtr = 0;
		options[optionPtr].color = hoverColor;
	}

	void operator--() {
		options[optionPtr].color = linkColor;
		if (optionPtr == 0) optionPtr = options.size() - 1;
		else --optionPtr;
		options[optionPtr].color = hoverColor;
	}

	void doAction() {
		options[optionPtr].color = actionColor;
		show();
		Sleep(250);
		options[optionPtr].action();
		options[optionPtr].color = hoverColor;
	}

	void show() {
		clear();
		int k = 0;
		for (int i = 0; i < options.size(); ++i) {
			Console::showString(options[i].name, position.x, position.y + i + k, options[i].color);
			k += space;
		}
	}

	void clear() {
		int k = 0;
		for (int i = 0; i < options.size(); ++i) {
			Console::clearString(position.x, position.y + i + k, options[i].name.length());
			k += space;
		}
	}

private:
	std::vector<Option> options;
	Position position;
	int optionPtr;

	static const int actionColor = 12;
	static const int hoverColor = 11;
	static const int linkColor = 8;	
	static const int space = 1;
};

