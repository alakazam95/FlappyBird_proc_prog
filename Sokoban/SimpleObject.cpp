#include "SimpleObject.h"


SimpleObject::SimpleObject() : Object() {
	this->color = 1;
	this->ch = ' ';
	stateChanged = false;
}

SimpleObject::SimpleObject(Position pposition, char character, int color) : Object(pposition) {
	this->ch = character;
	this->color = color;
	stateChanged = false;
}

SimpleObject::SimpleObject(const SimpleObject& sobj) : Object(sobj) {
	this->ch = sobj.ch;
	this->color = sobj.color;
	stateChanged = false;
}

SimpleObject::~SimpleObject() {

}

void SimpleObject::setCharacter(char ch) {
	this->ch = ch;
	stateChanged = true;
}

char SimpleObject::getCharacter() {
	return this->ch;
}

void SimpleObject::draw() {
	stateChanged = false;
	if(this->ch != ' ' && this->color != 0)
	Console::draw(position.x, position.y, color, this->ch);
}


void SimpleObject::clear() {
	if (this->ch != ' ' && this->color != 0)
	Console::clear(position.x, position.y);
}



void SimpleObject::setColor(int color) {
	this->color = color;
	stateChanged = true;
}

int SimpleObject::getColor() const {
	return this->color;
}

void SimpleObject::up() {
	position.y -= 1;
	stateChanged = true;
}

void SimpleObject::down() {
	position.y += 1;
	stateChanged = true;
}

void SimpleObject::left() {
	position.x -= 1;
	stateChanged = true;
}

void SimpleObject::right() {
	position.x += 1;
	stateChanged = true;
}

void SimpleObject::move(int dx, int dy) {
	position.x += dx;
	position.y += dy;
	stateChanged = true;
}

bool SimpleObject::collision(const Object& obj) const {
	if (this->ch == ' ' || this->color == 0) return false;
	return this->position == obj.getPosition();
}

Object* SimpleObject::clone() {
	return new SimpleObject(*this);
}

bool SimpleObject::checkStateChanged() {
	return stateChanged;
}



