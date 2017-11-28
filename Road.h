#pragma once
#include "includes.h"
class Road {
	vector<Lane*> lanes;
	Window* window;
public:
	Road(Window*);
	~Road();
	template<class T>
	void addLane(int, int, int, double, int);
	void run();
	bool crash(People*);
	void draw();
	void reset();
};

Road::Road(Window* w) {
	srand(time(NULL));
	window = w;
}
Road::~Road() {
	for (auto& x: lanes)
		delete x;
}
void Road::draw() {
	for (auto& x: lanes)
		x->draw();
}
void Road::run() {
	for (auto& x: lanes)
		x->run();
}
void Road::reset() {
	for (auto& x: lanes)
		x->reset();
}
bool Road::crash(People* player) {
	for (auto& x: lanes)
		if (x->crash(player))
			return true;
	return false;
}
template<class T>
void Road::addLane(int safeDistX, int safeDistY, int count, double speed, int y = 0) {
	int last = 0;
	if (lanes.size())
		last = lanes.back()->getX() + lanes.back()->getHeight();
	Lane* newLane = new Lane(window, last + safeDistX, y, speed);
	while (count--)
		newLane->add(new T(window), safeDistY);
	lanes.push_back(newLane);
}