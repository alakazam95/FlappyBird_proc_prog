#pragma once

#include "Position.h"

class Object {
public:
	virtual void up() = 0;
	virtual void down() = 0;
	virtual void left() = 0;
	virtual void right() = 0;

	virtual void move(int dx, int dy) = 0;

	virtual void draw() = 0;
	virtual void clear() = 0;

	virtual bool collision(const Object& obj) const=0;
	virtual void setColor(int color) = 0;


	Object();
	Object(Position position);
	Object(const Object& obj);
	virtual ~Object();
	virtual Object* clone() = 0;

	Position getPosition() const;
	virtual void setPosition(Position position);

	virtual bool checkStateChanged() = 0;

protected:
	Position position;


};