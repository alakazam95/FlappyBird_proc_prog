#pragma once

class Position {
public:

	int x;
	int y;

	Position();

	Position(int x, int y);

	void setPosition(int x, int y);

	bool operator==(const Position& pos) const;

};