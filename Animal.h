// fuck you who read this
#pragma once
#include "includes.h"
class Animal: public Object {
public:
	Animal() {}
	~Animal() {}
};
class Snake: public Animal {
public:
	Snake() {
		shape = Shape::DefaultShape[6];
	}
};
class Bird: public Animal {
public:
	Bird() {
		shape = Shape::DefaultShape[2];
	}
};
class Dinosaur: public Animal {
public:
	Dinosaur() {
		shape = Shape::DefaultShape[5];
	}
};