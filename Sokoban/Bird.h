#pragma once

#include <vector>
#include "ComplexObject.h"
#include "SimpleObject.h"

class Bird : public ComplexObject {

public:
	Bird(Position position);
	Bird(Position position, std::string path, int color);
	Bird(const Bird& bird);
	virtual ~Bird();
	void jump();

	virtual Object* clone();

	void turnLeft();
	void turnRight();
	
	void addPoint();
	int getPoints();

protected:
	virtual void build();
	void setDefaults();
	
private:
	int points;

};