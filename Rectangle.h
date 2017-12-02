#pragma once
#include "includes.h"
class Rectangle {
protected:
	Point coord; // save
	int width; // save
	int height; // save
public:
	int& getX();
	int& getY();
	int& getWidth();
	int& getHeight();
	void setCoord(int, int);
	void setSize(int, int);
	Rectangle(Point, int, int);
	~Rectangle() {}
};

Rectangle::Rectangle(Point _coord = Point(0, 0), int _width = 0, int _height = 0) {
	coord = _coord;
	width = _width;
	height = _height;
}
int& Rectangle::getX() {
	return coord.getX();
}
int& Rectangle::getY() {
	return coord.getY();
}
int& Rectangle::getHeight() {
	return height;
}
int& Rectangle::getWidth() {
	return width;
}
void Rectangle::setCoord(int x, int y) {
	coord = Point(x, y);
}
void Rectangle::setSize(int _width, int _height) {
	width = _width;
	height = _height;
}