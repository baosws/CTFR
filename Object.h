#pragma once
#include "includes.h"
class Object {
protected:
	Window* window;
	PointF coord;
	Shape* shape;
public:
	Object(Window*, double, double, int);
	~Object();
	int getWidth();
	int getHeight();
	double& getX();
	double& getY();
	virtual void move(double, double);
	virtual void draw(double, double, Window*);
	bool isNullCell(double, double);
	bool isImpact(Object*);
	friend class Lane;
};

Object::Object(Window* w, double _x = 0, double _y = 0, int shapeType = 0) {
	window = w;
	coord = PointF(_x, _y);
	shape = &Shape::DefaultShape[shapeType];
}
void Object::move(double dx, double dy) {
	coord.getX() += dx;
	coord.getY() += dy;
}
void Object::draw(double dx = 0, double dy = 0, Window* w = NULL) {
	if (!w)
		w = window;
	shape->draw(coord.getX() + dx, coord.getY() + dy, w);
}
Object::~Object() {}
double& Object::getY() {
	return coord.getY();
}
double& Object::getX() {
	return coord.getX();
}
int Object::getWidth() {
	return shape->getWidth();
}
int Object::getHeight() {
	return shape->getHeight();
}
bool Object::isNullCell(double i, double j) {
	return shape->isNullCell(i - coord.getX(), j - coord.getY());
}
bool Object::isImpact(Object* p) {
	for (int i = coord.getX(); i < coord.getX() + shape->getHeight(); i++)
		for (int j = coord.getY(); j < coord.getY() + shape->getWidth(); j++)
			if (!isNullCell(i, j) && !p->isNullCell(i, j))
				return true;
	return false;
}
