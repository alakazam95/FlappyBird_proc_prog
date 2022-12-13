#pragma once

#include "Windows.h"
#include <iostream>
#include <string>

class Console {
private:

	static const int WIDTH = 80;
	static const int HEIGHT = 25;

	static void gotoxy(int x, int y) {
		COORD p;
		p.X = x;
		p.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}

	static void set_color(int c) {
		HANDLE uchwyt;
		uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(uchwyt, c);
	}

public:

	static void showString(std::string value, int x, int y, int color) {
		gotoxy(x, y);
		set_color(color);
		std::cout << value;
	}

	static void clearString(int x, int y, int size) {
		for (int i = 0; i < size; ++i) {
			gotoxy(x + i, y);
			std::cout << " ";
		}
	}

	static void showConsoleCursor(bool showFlag) {
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	static void setWindowSize(int width, int height) {
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r);
		MoveWindow(console, r.left, r.top, width, height, TRUE);
	}

	static void draw(int x, int y, int color, char chr) {
		if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT)) {
			Console::gotoxy(x, y);
			Console::set_color(color);
			std::cout << chr;
		}
	}

	static void draw_force(int x, int y, int color, char chr) {
			Console::gotoxy(x, y);
			Console::set_color(color);
			std::cout << chr;
	}

	static void clear(int x, int y) {
		if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT)) {
			gotoxy(x, y);
			std::cout << " ";
		}
	}
};

/*
set_color(c):
c=
0 czarny
1 niebieski ciemny
2 zielony
3 turkus
4 czerwony
5 rozowy
6 zolty
7 bialy
8 szary
9 niebieski jasny
10 zielony jasny
11 turkus jasny
12 czerwony jasny
13 rozowy jasny
14 zolty jasny
15 bialy jasny

*/


