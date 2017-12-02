#pragma once
#include "includes.h"
class Lane: public Rectangle {
	Window* window; // not save
	double speed; // save
	vector<Object*> objects; // save
	TrafficLight trafficLight; // save
	int fullWidth = 0; // save
public:
	Lane(Window*, int, int, double);
	~Lane();
	bool crash(Player*);
	void run();
	void reset();
	void add(Object*, int);
	void draw();
	void speedUp(double);
	int getHeight();
};

Lane::Lane(Window* w, int x, int y, double _speed = -1) {
	window = w;
	coord = Point(x, y);
	speed = _speed;
}
Lane::~Lane() {
	for (auto& x: objects)
		delete x;
}
bool Lane::crash(Player* p) {
	for (auto& x: objects)
		if (x->isImpact(p))
			return true;
	return false;
}
void Lane::run() {
	fullWidth = max(fullWidth, window->getWidth());
	if (!trafficLight.isStopped())
		for (auto& x: objects)
			x->move(speed * dx[0], speed * dy[0]);
	for (auto& x: objects)
		if (x->getY() >= coord.getY() + fullWidth)
			x->getY() -= fullWidth;
		else if (x->getY() + x->getWidth() - 1 < coord.getY())
			x->getY() += fullWidth;
	trafficLight.update();
}
void Lane::add(Object* obj, int safeDistance = 4) {
	fullWidth += safeDistance;
	obj->getY() = coord.getY() + fullWidth;
	fullWidth += obj->getWidth();
	obj->getX() = coord.getX();
	objects.push_back(obj);
}
void Lane::draw() {
	for (auto& x: objects)
		x->draw();
}
void Lane::reset() {
	if (objects.empty())
		return;
	double dy = objects[0]->getY();
	for (auto& x: objects) {
		x->getY() -= dy;
		if (x->getY() + x->getWidth() - 1 < 0)
			x->getY() += fullWidth;
		else if (x->getY() >= fullWidth)
			x->getY() -= fullWidth;
	}
}
int Lane::getHeight() {
	int res = 0;
	for (auto& x: objects)
		res = max(res, x->getHeight());
	return res;
}