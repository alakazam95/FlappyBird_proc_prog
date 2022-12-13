#include "ComplexObject.h"

ComplexObject::ComplexObject() : currentFrame(0) {
	def_velX = 0;
	def_velY = 0;
	def_aX = 0;
	def_aY = 0;
}

ComplexObject::ComplexObject(Position position) : Object(position), currentFrame(0) {

}

ComplexObject::ComplexObject(std::string path, int color) : currentFrame(0) {
	if (buildFromFile(path, color) < 0) 
	{ std::cout << "build error" << path << std::endl; _getch(); exit(1); }
}

ComplexObject::ComplexObject(const ComplexObject& obj) : Object(obj) {
	currentFrame = obj.currentFrame;
	def_velX = obj.def_velX;
	def_velY = obj.def_velY;
	def_aX = obj.def_aX;
	def_aY = obj.def_aY;

	velX = obj.velX;
	velY = obj.velY;
	aX = obj.aX;
	aY = obj.aY;

	for (int i = 0; i < obj.frames.size(); ++i) {
		std::vector<Object*>* frame = new std::vector<Object*>;
		for (int j = 0; j < obj.frames[i]->size(); ++j) {
			frame->push_back((*obj.frames[i])[j]->clone());
		}
		this->frames.push_back(frame);
	}
}

int ComplexObject::buildFromFile(std::string path, int color) {
	std::fstream file;
	file.open(path, std::ios::in);
	if (file.good()) {
		int x = 0, y = 0;
		std::string line;
		while (	getline(file, line) && line != "END") {
			if (line != "NF") {
				if (frames.size() == 0) frames.push_back(new std::vector<Object*>());
				for (int i = 0; i < line.length(); ++i) {
					int size = frames.size();
					if (line[i] == '?') frames[size - 1]->push_back(new SimpleObject(Position(x+i, y), ' ', 0));
					else frames[size - 1]->push_back(new SimpleObject(Position(x+i, y), line[i], color));
				} ++y;
			}
			else { frames.push_back(new std::vector<Object*>()); y = 0; }
		}
	}
	else { std::cout << "file " << path << " can't be download" << std::endl;  return -1; }

	file.close();

	return 0;
}

ComplexObject::~ComplexObject() {
	for (int i = 0; i < frames.size(); ++i) {
		if (frames[i] == NULL) continue;
		for (int j = 0; j < frames[i]->size(); ++j) {
			if ((*frames[i])[j]) delete (*frames[i])[j];
		}
		delete frames[i];
	}
	frames.clear();
}

void ComplexObject::up() {
	if (frames.size() == 0) return;
	this->position.y -= 1;
	for (int j = 0; j < frames.size(); ++j) {
		std::vector<Object*>* elements = frames[j];
		for (int i = 0; i < elements->size(); ++i) {
			(*elements)[i]->up();
		}
	}
}

void ComplexObject::down() {
	if (frames.size() == 0) return;
	this->position.y += 1;
	for (int j = 0; j < frames.size(); ++j) {
		std::vector<Object*>* elements = frames[j];
		for (int i = 0; i < elements->size(); ++i) {
			(*elements)[i]->down();
		}
	}
}

void ComplexObject::left() {
	if (frames.size() == 0) return;
	this->position.x -= 1;
	for (int j = 0; j < frames.size(); ++j) {
		std::vector<Object*>* elements = frames[j];
		for (int i = 0; i < elements->size(); ++i) {
			(*elements)[i]->left();
		}
	}
}

void ComplexObject::right() {
	if (frames.size() == 0) return;
	this->position.x += 1;
	for (int j = 0; j < frames.size(); ++j) {
		std::vector<Object*>* elements = frames[j];
		for (int i = 0; i < elements->size(); ++i) {
			(*elements)[i]->right();
		}
	}
}

void ComplexObject::move(int dx, int dy) {
	this->position.x += dx;
	this->position.y += dy;
	if (frames.size() == 0) return;
	for (int j = 0; j < frames.size(); ++j) {
		std::vector<Object*>* elements = frames[j];
		for (int i = 0; i < elements->size(); ++i) {
			(*elements)[i]->move(dx, dy);
		}
	}
}

void ComplexObject::setColor(int color) {
	if (frames.size() == 0) return;
	for (int j = 0; j < frames.size(); ++j) {
		std::vector<Object*>* elements = frames[j];
		for (int i = 0; i < elements->size(); ++i) {
			(*elements)[i]->setColor(color);
		}
	}
}

void ComplexObject::draw() {
	if (frames.size() == 0) return;
	std::vector<Object*>* elements = frames[currentFrame];
	for (int i = 0; i < elements->size(); ++i) {
		(*elements)[i]->draw();
	}
}

void ComplexObject::clear() {
	if (frames.size() == 0) return;
	std::vector<Object*>* elements = frames[currentFrame];
	for (int i = 0; i < elements->size(); ++i) {
		(*elements)[i]->clear();
	}
}

bool ComplexObject::collision(const Object& obj) const {
	if (frames.size() == 0) return false;
	if (dynamic_cast<const ComplexObject*>(&obj)) {
		const ComplexObject* cobj = reinterpret_cast<const ComplexObject*>(&obj);
		std::vector<Object*>* objElements = cobj->getCurrentFrame();
		std::vector<Object*>* elements = frames[currentFrame];
		for (int i = 0; i < elements->size(); ++i) {
			for (int j = 0; j < objElements->size(); ++j) {
				if ((*elements)[i]->collision(*(*objElements)[j])) return true;
			}
		}
	}
	else {
		std::vector<Object*>* elements = frames[currentFrame];
		for (int i = 0; i < elements->size(); ++i) {
			if ((*elements)[i]->collision(obj))
				return true;
		}
	}
	return false;
}

std::vector<Object*>* ComplexObject::getCurrentFrame() const {
	return this->frames[currentFrame];
}

void ComplexObject::setPosition(Position position) {
	int dx = position.x - this->position.x;
	int dy = position.y - this->position.y;
	//this->position = position;
	this->move(dx, dy);
}

void ComplexObject::update(int time) { 
	
	if ((time - aX.lastTime) >= abs(1000.0 / aX.value)) {
		//изм скорости Х
		aX.lastTime = time;
	}
	if ((time - aY.lastTime) >= abs(1000.0 / aY.value)) {
		//изм скорости по y
		velY.value += aY.value;
		aY.lastTime = time;
	}
	if ( (velX.value != 0) && ( (time - velX.lastTime) >= abs(1000.0 / velX.value) ) ) {
		//изм позиции x
		Position newPosition(this->position.x, this->position.y);
		newPosition.x += velX.value / abs(velX.value);
		this->setPosition(newPosition);
		velX.lastTime = time;
	}
	if ( (velY.value != 0) && ( (time - velY.lastTime) >= abs(1000 / velY.value) ) ) {
		//аналогично по y
		Position newPosition(this->position.x, this->position.y);
		newPosition.y += velY.value / abs(velY.value);
		this->setPosition(newPosition);
		velY.lastTime = time;
	}
}

void ComplexObject::setDefVelX(int value) {
	this->def_velX = value;
}

void ComplexObject::setDefVelY(int value) {
	this->def_velY = value;
}

void ComplexObject::setDefAX(int value) {
	this->def_aX = value;
}

void ComplexObject::setDefAY(int value) {
	this->def_aY = value;
}

Component::Component() {
	value = 0;
	lastTime = 0;
}

bool ComplexObject::checkStateChanged() {
	if (frames.size() == 0) return false;
	std::vector<Object*>* elements = frames[currentFrame];
	for (int i = 0; i < elements->size(); ++i) {
		if ((*elements)[i]->checkStateChanged()) return true;
	}
	return false;
}

void ComplexObject::randomCurrentFrame() {
	currentFrame = rand() % frames.size();
}