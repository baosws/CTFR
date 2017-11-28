#pragma once
#include "includes.h"
class Vehicle: public Object {
public:
	Vehicle(Window* w): Object(w) {}
};
class Truck: public Vehicle {
public:
	Truck(Window* w): Vehicle(w) {
		shape = &Shape::DefaultShape[4];
	}
};
class Car: public Vehicle {
public:
	Car(Window* w): Vehicle(w) {
		shape = &Shape::DefaultShape[1];
	}
};
class Plane: public Vehicle {
public:
	Plane(Window* w): Vehicle(w) {
		shape = &Shape::DefaultShape[3];
	}
};