#pragma once
#include "includes.h"
const int DEFAULT_GO = 500;
const int DEFAULT_STOP = 100;
class TrafficLight {
	int stop; // save
	int go; // save
	int now = 0; // save
public:
	TrafficLight(int, int);
	~TrafficLight() {}
	void update();
	bool isStopped();
};
TrafficLight::TrafficLight(int _go = DEFAULT_GO, int _stop = DEFAULT_STOP): go(_go), stop(_stop) {
	now = rand() % (stop + go);
}
void TrafficLight::update() {
	now = (now + 1) % (stop + go);
}
bool TrafficLight::isStopped() {
	return now >= go;
}
