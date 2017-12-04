#pragma once
#include "../includes.h"
const int DEFAULT_GO = 500;
const int DEFAULT_STOP = 100;
class TrafficLight: public Object {
	int stop; // save
	int go; // save
	int now = 0; // save
public:
	TrafficLight(Window*, double, int, int);
	~TrafficLight() {}
	void update();
	bool isStopped();
	void reset();
	void save(XMLDocument* doc, XMLElement* root);
	void load(XMLElement* root);
	void draw();
};
void TrafficLight::reset() {
	now = rand() % (stop + go);
}
TrafficLight::TrafficLight(Window* w, double x, int _go = DEFAULT_GO, int _stop = DEFAULT_STOP): Object(w, x, 0) {
	go = _go;
	stop = _stop;
	reset();
}
void TrafficLight::update() {
	now = (now + 1) % (stop + go);
}
bool TrafficLight::isStopped() {
	return now >= go;
}
void TrafficLight::draw() {
	if (isStopped())
		shapeID = 7;
	else
		shapeID = 8;
	coord.getY() = 0;
	Object::draw();
	coord.getY() = window->getWidth() - 1;
	Object::draw();
}
void TrafficLight::save(XMLDocument* doc, XMLElement* root) {
	XMLElement* trafficLight = doc->NewElement("trafficLight");
	
	trafficLight->SetAttribute("coordX", coord.getX());
	trafficLight->SetAttribute("stop", stop);
	trafficLight->SetAttribute("go", go);
	trafficLight->SetAttribute("now", now);

	root->InsertEndChild(trafficLight);
}
void TrafficLight::load(XMLElement* root) {
	cerr << "loading a trafficLight\n";
	XMLElement* trafficLight = root->FirstChildElement("trafficLight");
	trafficLight->QueryDoubleAttribute("coordX", &coord.getX());
	trafficLight->QueryIntAttribute("stop", &stop);
	trafficLight->QueryIntAttribute("go", &go);
	trafficLight->QueryIntAttribute("now", &now);
	cerr << "a trafficLight loaded\n";
}