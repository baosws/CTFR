#pragma once
#include "includes.h"
class Object {
protected:
	Window* window;
	PointF coord; // save
	int shapeID; // save
private:
	bool isNullCell(double, double);
public:
	Object(Window*, double, double, int);
	~Object();
	int getWidth();
	int getHeight();
	double& getX();
	double& getY();
	virtual void move(double, double);
	virtual void draw();
	bool isImpact(Object*);
	friend class Lane;
};

Object::Object(Window* w, double _x = 0, double _y = 0, int shapeType = 0) {
	window = w;
	coord = PointF(_x, _y);
	shapeID = shapeType;
}
void Object::move(double dx, double dy) {
	coord.getX() += dx;
	coord.getY() += dy;
}
void Object::draw() {
	Shapes[shapeID].draw(coord.getX(), coord.getY(), window);
}
Object::~Object() {}
double& Object::getY() {
	return coord.getY();
}
double& Object::getX() {
	return coord.getX();
}
int Object::getWidth() {
	return Shapes[shapeID].getWidth();
}
int Object::getHeight() {
	return Shapes[shapeID].getHeight();
}
bool Object::isNullCell(double i, double j) {
	return Shapes[shapeID].isNullCell(i - coord.getX(), j - coord.getY());
}
bool Object::isImpact(Object* p) {
	for (int i = coord.getX(); i < coord.getX() + getHeight(); i++)
		for (int j = coord.getY(); j < coord.getY() + getWidth(); j++)
			if (!isNullCell(i, j) && !p->isNullCell(i, j))
				return true;
	return false;
}
