#pragma once
#include "includes.h"
class Lane: public Rectangle {
	double speed;
	int timeToGo;
	vector<Object*> objects;
	int fullWidth;
	Window* window;
	TrafficLight* trafficLight;
public:
	Lane(Window*, int, int, double, int);
	~Lane();
	bool crash(People*);
	void run();
	void reset();
	void add(Object*, int);
	void draw(Window*);
	void speedUp(double);
	int getHeight();
};

Lane::Lane(Window* w, int x, int y, double _speed = -1, int _width = -1) {
	window = w;
	coord = Point(x, y);
	if (_width == -1)
		_width = w->getWidth();
	width = _width;
	speed = _speed;
	fullWidth = 0;
	trafficLight = new TrafficLight();
}
Lane::~Lane() {
	for (auto& x: objects)
		delete x;
	delete trafficLight;
}
bool Lane::crash(People* p) {
	for (auto& x: objects)
		if (x->isImpact(p))
			return true;
	return false;
}
void Lane::run() {
	fullWidth = max(width, fullWidth);
	if (!trafficLight->isStopped())
		for (auto& x: objects)
			x->move(speed * dx[0], speed * dy[0]);
	for (auto& x: objects)
		if (x->getY() >= coord.getY() + fullWidth)
			x->getY() -= fullWidth;
		else if (x->getY() + x->getWidth() - 1 < coord.getY())
			x->getY() += fullWidth;
	trafficLight->update();
}
void Lane::add(Object* obj, int safeDistance = 4) {
	fullWidth += safeDistance;
	obj->getY() = coord.getY() + fullWidth;
	obj->getX() = coord.getX();
	objects.push_back(obj);
	fullWidth += obj->getWidth();
}
void Lane::draw(Window* w = NULL) {
	for (auto& x: objects)
		x->draw(0, 0, w);
}
void Lane::reset() {
	if (objects.empty())
		return;
	double dx = objects[0]->getY();
	for (auto& x: objects) {
		x->getY() -= dx;
		if (x->getY() + x->getWidth() - 1 < 0)
			x->getY() += fullWidth;
		else if (x->getY() >= fullWidth)
			x->getY() -= fullWidth;
	}
}
void Lane::speedUp(double accelebrator) {
	speed *= accelebrator;
	if (speed >= 1)
		speed = 1;
}
int Lane::getHeight() {
	int res = 0;
	for (auto& x: objects)
		res = max(res, x->getHeight());
	return res;
}