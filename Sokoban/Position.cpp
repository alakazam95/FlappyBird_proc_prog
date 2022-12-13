#include "Position.h"

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

void Position::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Position::operator==(const Position& pos) const {
	if (pos.x == x && pos.y == y) return true;
	return false;
}