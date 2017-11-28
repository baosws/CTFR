#pragma once
#include "includes.h"
class People: public Object {
	bool dead = false;
public:
	People(Window*, double, double);
	~People() {}
	void move(double, double);
	void move(int);
	bool isFinish(int);
	bool isDead();
	void die();
	void revive();
};

People::People(Window* w, double x = 0, double y = 0): Object(w, x, y) {
	dead = false;
}
bool People::isFinish(int dest) {
	return coord.getX() == dest;
}
void People::die() {
	dead = true;
}
void People::revive() {
	dead = false;
}
bool People::isDead() {
	return dead;
}
void People::move(int dir) {
	move(dx[dir], dy[dir]);
}
void People::move(double dx, double dy) {
	Object::move(dx, dy);
	cerr << getX() << "" << getY() << "\t" << window->getHeight() << " " << window->getWidth() << endl;
	if (   getX() < window->getX()
		|| getX() + getHeight() >= window->getX() + window->getHeight()
		|| getY() < window->getY()
		|| getY() + getWidth() >= window->getY() + window->getWidth())
			Object::move(-dx, -dy);
}