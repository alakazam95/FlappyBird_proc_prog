#include "ScrollTube.h"

bool ScrollTube::initialProcess = true;

ScrollTube::ScrollTube(Bird* bird) :ComplexObject(Position(80,0)) {
	this->bird = bird;
	currentFrame = 0;
	initialProcess = true;
	build();
	initialProcess = false;

	def_velX = 0;
	def_velY = 0;
	def_aX = 0;
	def_aY = 0;

	direction = -1;

	setColor(1);

}

ScrollTube::ScrollTube(const ScrollTube& scrollTube) : ComplexObject(scrollTube) {
	setPosition(position);
}

ScrollTube::~ScrollTube() {

}

Object* ScrollTube::clone() {
	return new ScrollTube(*this);
}

void ScrollTube::build() {
	int x = 80, y = 0;
	std::vector<Object*>* elements = new std::vector<Object*>;
	elements->push_back(new Tube(Position(x, y), "tube.txt", 8));
	elements->push_back(new Tube(Position(x + 35, y), "tube.txt", 8));
	elements->push_back(new Tube(Position(x + 70, y), "tube.txt", 8));
	//elements->push_back(new Tube(Position(x + 105, y), "tube.txt", 8));

	frames.push_back(elements);
}

void ScrollTube::update(int time) {
	ComplexObject::update(time);
	
	Object* tube = (*frames[currentFrame])[0];
	
	//give points for player
	static bool lock = false;
	if (tube->getPosition().x + Tube::width < bird->getPosition().x && !lock) {
		bird->addPoint();
		lock = true;
	}

	
	if (tube->getPosition().x < -Tube::width) {
		//this->setColor(rand() % 10 + 1);
		frames[currentFrame]->erase(frames[currentFrame]->begin());
		ScrollTube::initialProcess = true;
		((Tube*)tube)->randomCurrentFrame();
		tube->setPosition(Position(105, 0));
		lock = false;
		ScrollTube::initialProcess = false;
		frames[currentFrame]->push_back(tube);
	} 
}

void ScrollTube::startScroll() {
	velX.value = direction * 25;
	//this->aX.value = -2;
}
void ScrollTube::stopScroll() {
	velX.value = 0;
}
