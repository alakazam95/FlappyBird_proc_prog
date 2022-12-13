#pragma once

#include "Object.h"
#include <vector>
#include "Timer.h"
#include <cmath>
#include <fstream>
#include <string>
#include "SimpleObject.h"
#include <conio.h>

struct Component {
	int value;
	int lastTime;

	Component();
};

class ComplexObject : public Object {
public:
	ComplexObject();
	ComplexObject(Position position);
	ComplexObject(std::string path, int color);
	ComplexObject(const ComplexObject& obj);

	virtual ~ComplexObject();
	virtual void setPosition(Position position);
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();

	virtual void move(int dx, int dy);

	virtual void draw();
	virtual void clear();

	virtual bool collision(const Object& obj) const;

	virtual void update(int time);

	void setDefVelX(int value);
	void setDefVelY(int value);
	void setDefAX(int value);
	void setDefAY(int value);

	virtual Object* clone() = 0;

	virtual bool checkStateChanged();

	std::vector<Object*>* getCurrentFrame() const;

	void randomCurrentFrame();

	void setColor(int color);

protected:
	std::vector<std::vector<Object*>*> frames;
	int currentFrame;

	//временно используется для выполнения операций над объектом 
	Component velX;
	Component velY;
	Component aX;
	Component aY;
	//defolt 
	int def_velX;
	int def_velY;
	int def_aX;
	int def_aY;

	virtual void build()=0;

	int buildFromFile(std::string path, int color);

};
