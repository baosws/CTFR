#pragma once
#include "../includes.h"

class Obstacle: public Object {
public:
	static Object* _load(Window*, XMLElement*);
	Obstacle(Window* w): Object(w) {}
};

class Snake: public Obstacle {
public:
	Snake(Window* w): Obstacle(w) {
		shapeID = 6;
	}
};
class Bird: public Obstacle {
public:
	Bird(Window* w): Obstacle(w) {
		shapeID = 2;
	}
};
class Dinosaur: public Obstacle {
public:
	Dinosaur(Window* w): Obstacle(w) {
		shapeID = 5;
	}
};

class Truck: public Obstacle {
public:
	Truck(Window* w): Obstacle(w) {
		shapeID = 4;
	}
};
class Car: public Obstacle {
public:
	Car(Window* w): Obstacle(w) {
		shapeID = 1;
	}
};
class Plane: public Obstacle {
public:
	Plane(Window* w): Obstacle(w) {
		shapeID = 3;
	}
};

Object* Obstacle::_load(Window* w, XMLElement* node) {
	int id;
	node->QueryIntAttribute("shapeID", &id);
	Object* obj;
	if (id == 1)
		obj = new Car(w);
	else if (id == 2)
		obj = new Bird(w);
	else if (id == 3)
		obj = new Plane(w);
	else if (id == 4)
		obj = new Truck(w);
	else if (id == 5)
		obj = new Dinosaur(w);
	else if (id == 6)
		obj = new Snake(w);
	obj->load(node);
	return obj;
}