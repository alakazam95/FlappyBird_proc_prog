#pragma once

#include "Position.h"
#include "Console.h"
#include "Object.h"
#include "SetPosition.h"
#include <iostream>
#include <string>

class SimpleObject : public Object {

public:

	SimpleObject();
	SimpleObject(Position pposition, char character, int color);
	SimpleObject(const SimpleObject& sobj);
	virtual ~SimpleObject();
	void setCharacter(char ch);
	char getCharacter();
	void setColor(int color);
	int getColor() const;

	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();

	virtual void move(int dx, int dy);

	virtual void draw();
	virtual void clear();

	virtual bool collision(const Object& obj) const;

	virtual Object* clone();

	virtual bool checkStateChanged();

private:
	char ch;
	int color;
	bool stateChanged;
	Object* older;

	

};
