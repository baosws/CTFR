#pragma once
#include "../includes.h"
class Point {
	int x, y; // save
public:
	int& getX();
	int& getY();
	Point(int, int);
	~Point() {}
};
int& Point::getX() {
	return x;
}
int& Point::getY() {
	return y;
} 
Point::Point(int _x = 0, int _y = 0) {
	x = _x;
	y = _y;
}