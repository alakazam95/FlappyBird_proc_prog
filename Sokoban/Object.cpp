#include "Object.h"

Object::Object() : position(0, 0) {

}

Object::Object(Position position) {
	this->position = position;
}

Object::~Object() {

}

Object::Object(const Object& obj) {
	position = obj.position;
}

Position Object::getPosition() const {
	return position;
}
void Object::setPosition(Position position) {
	this->position = position;
}


