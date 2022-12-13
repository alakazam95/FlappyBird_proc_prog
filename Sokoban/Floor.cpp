#include "Floor.h"

Floor::Floor(Position position, std::string path, int color) : ComplexObject(path, color) {
	setPosition(position);
}

Floor::Floor(const Floor& floor) : ComplexObject(floor) {
	setPosition(position);
}

Floor::~Floor() {

}

Object* Floor::clone() {
	return new Floor(*this);
}

void Floor::build() {}