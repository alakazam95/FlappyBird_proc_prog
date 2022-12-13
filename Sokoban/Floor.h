#pragma once
#include "ComplexObject.h"

class Floor : public ComplexObject {

public:
	Floor(Position position, std::string path, int color);
	Floor(const Floor& floor);
	virtual ~Floor();
	virtual Object* clone();

protected:
	virtual void build();

};