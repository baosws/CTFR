#pragma once
#include "../includes.h"
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
	void reset();
	void save(XMLDocument* doc, XMLElement* root) {
		XMLElement* trafficLight = doc->NewElement("trafficLight");
		
		trafficLight->SetAttribute("stop", stop);
		trafficLight->SetAttribute("go", go);
		trafficLight->SetAttribute("now", now);

		root->InsertEndChild(trafficLight);
	}
	void load(XMLElement* root) {
		cerr << "loading a trafficLight\n";
		XMLElement* trafficLight = root->FirstChildElement("trafficLight");
		trafficLight->QueryIntAttribute("stop", &stop);
		trafficLight->QueryIntAttribute("go", &go);
		trafficLight->QueryIntAttribute("now", &now);
		cerr << "a trafficLight loaded\n";
	}
};
void TrafficLight::reset() {
	now = rand() % (stop + go);
}
TrafficLight::TrafficLight(int _go = DEFAULT_GO, int _stop = DEFAULT_STOP): go(_go), stop(_stop) {
	reset();
}
void TrafficLight::update() {
	now = (now + 1) % (stop + go);
}
bool TrafficLight::isStopped() {
	return now >= go;
}
