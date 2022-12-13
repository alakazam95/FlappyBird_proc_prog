#include "Logo.h"

Logo::Logo(Position position, std::string path, int color) : ComplexObject(path, color) {
	setPosition(position);
}

Logo::Logo(const Logo& bird) : ComplexObject(bird) {
	
}

 Logo::~Logo() {

}

Object* Logo::clone() {
	return new Logo(*this);
}

void Logo::update(int time) {

	static int lastTime = 0;
	static const int velocity = 15;
	static int color = rand() % 15 + 1;
	static int index = 0;

	if ((time - lastTime) >= abs(1000.0 / velocity)) {
		if (index == frames[currentFrame]->size()) {
			color = rand() % 15 + 1;
			index = 0;
		}
		else {
			while (((SimpleObject*)(*frames[currentFrame])[index])->getCharacter() == ' ') ++index;
			(*frames[currentFrame])[index]->setColor(color);
			++index;
		}
		lastTime = time;
	}

	ComplexObject::update(time);
}

void Logo::build() {}