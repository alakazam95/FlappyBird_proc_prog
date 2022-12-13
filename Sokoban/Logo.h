#pragma once

#include <vector>
#include "ComplexObject.h"
#include "SimpleObject.h"

class Logo : public ComplexObject {

public:
	Logo(Position position, std::string path, int color);
	Logo(const Logo& bird);
	virtual ~Logo();

	virtual Object* clone();
	virtual void update(int time);

protected:
	virtual void build();

};