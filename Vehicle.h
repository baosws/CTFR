#pragma once
#include "includes.h"
class Vehicle: public Object {
public:
	Vehicle() {}
};
class Truck: public Vehicle {
public:
	Truck() {
		shape = Shape::DefaultShape[4];
	}
};
class Car: public Vehicle {
public:
	Car() {
		shape = Shape::DefaultShape[1];
	}
};
class Plane: public Vehicle {
public:
	Plane() {
		shape = Shape::DefaultShape[3];
	}
};