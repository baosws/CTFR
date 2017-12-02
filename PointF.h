#pragma once
#include "includes.h"
class PointF {
	double x, y; // save
public:
	double& getX();
	double& getY();
	PointF(double, double);
	~PointF() {}
};
double& PointF::getX() {
	return x;
}
double& PointF::getY() {
	return y;
} 
PointF::PointF(double _x = 0, double _y = 0) {
	x = _x;
	y = _y;
}