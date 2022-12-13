#pragma once

#include "Tube.h"
#include "Bird.h"

class ScrollTube : public ComplexObject {

public:
	ScrollTube(Bird* bird);
	ScrollTube(const ScrollTube& tube);
	virtual ~ScrollTube();
	virtual Object* clone();
	virtual void update(int time);

	//TODO: test
	void startScroll();
	void stopScroll();

	static bool initialProcess;

protected:
	virtual void build();
	int direction; // left or right

private: 
	Bird* bird;


};