#pragma once
#include "includes.h"
class Animal: public Object {
public:
	Animal(Window* w): Object(w) {}
	~Animal() {}
};
class Snake: public Animal {
public:
	Snake(Window* w): Animal(w) {
		shape = &Shape::DefaultShape[6];
	}
};
class Bird: public Animal {
public:
	Bird(Window* w): Animal(w) {
		shape = &Shape::DefaultShape[2];
	}
};
class Dinosaur: public Animal {
public:
	Dinosaur(Window* w): Animal(w) {
		shape = &Shape::DefaultShape[5];
	}
};