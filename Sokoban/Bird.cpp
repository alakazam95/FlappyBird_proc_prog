#include "Bird.h"


Bird::Bird(Position position) {
	build();
	setPosition(position);
	setDefaults();
	points = 0;
}

Bird::Bird(Position position, std::string path, int color) : ComplexObject(path, color) {
	setPosition(position);
	setDefaults();
	points = 0;
}

Bird::Bird(const Bird& bird) : ComplexObject(bird) {
	setPosition(position);
	setDefaults();
	points = 0;
}

void Bird::setDefaults() {
	setDefVelX(10);
	setDefVelY(40);
	setDefAX(0);
	setDefAY(10);
}


Bird::~Bird() {

}

Object* Bird::clone() {
	return new Bird(*this);
}

void Bird::build() {
	int x = 0, y = 0;
	std::vector<Object*>* elements = new std::vector<Object*>;
	elements->push_back(new SimpleObject(Position(x + 3, y), '\\', 15));
	elements->push_back(new SimpleObject(Position(x + 4, y), '\\', 15));

	elements->push_back(new SimpleObject(Position(x + 3, y + 1), '(', 3));
	elements->push_back(new SimpleObject(Position(x + 4, y + 1), 'o', 9));
	elements->push_back(new SimpleObject(Position(x + 5, y + 1), '>', 3));

	elements->push_back(new SimpleObject(Position(x, y + 2), '\\', 4));
	elements->push_back(new SimpleObject(Position(x + 1, y + 2), '\\', 4));
	elements->push_back(new SimpleObject(Position(x + 2, y + 2), '_', 4));
	elements->push_back(new SimpleObject(Position(x + 3, y + 2), '/', 4));
	elements->push_back(new SimpleObject(Position(x + 4, y + 2), '/', 6));
	elements->push_back(new SimpleObject(Position(x + 5, y + 2), ')', 4));

	elements->push_back(new SimpleObject(Position(x + 1, y + 3), '\\', 4));
	elements->push_back(new SimpleObject(Position(x + 2, y + 3), '_', 4));
	elements->push_back(new SimpleObject(Position(x + 3, y + 3), '/', 6));
	elements->push_back(new SimpleObject(Position(x + 4, y + 3), '_', 4));
	elements->push_back(new SimpleObject(Position(x + 5, y + 3), ')', 4));

	elements->push_back(new SimpleObject(Position(x + 3, y + 4), '\"', 8));

	frames.push_back(elements);
}

void Bird::jump() {
	velY.value = -def_velY;
	aY.value = def_aY;
}

void Bird::turnLeft() {
	currentFrame = 1;
}
void Bird::turnRight() {
	currentFrame = 0;
}


void Bird::addPoint() {
	points += 1;
}

int Bird::getPoints() {
	return points;
}