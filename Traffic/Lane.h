#pragma once
#include "../includes.h"
class Lane {
	Window* window; // not save
	Point coord; // save
	double speed; // save
	vector<Object*> objects; // save
	TrafficLight* trafficLight; // save
	int fullWidth = 0; // save
public:
	Lane(Window*, int, int, double);
	~Lane();
	int& getX();
	int& getY();
	bool crash(Player*);
	void run();
	void reset();
	void add(Object*, int);
	void draw();
	void speedUp(double);
	int getHeight();
	void clear();
	void save(XMLDocument* doc, XMLElement* root, int id = 0);
	void load(XMLElement* lane);
};

Lane::Lane(Window* w, int x = 0, int y = 0, double _speed = -1) {
	window = w;
	coord = Point(x, y);
	speed = _speed;
	trafficLight = new TrafficLight;
}
void Lane::clear() {
	for (auto& x: objects)
		delete x;
	objects.clear();
	delete trafficLight;
}
Lane::~Lane() {
	clear();
}
int& Lane::getX() {
	return coord.getX();
}
int& Lane::getY() {
	return coord.getY();
}
bool Lane::crash(Player* p) {
	for (auto& x: objects)
		if (x->isImpact(p))
			return true;
	return false;
}
void Lane::run() {
	fullWidth = max(fullWidth, window->getWidth());
	if (!trafficLight->isStopped())
		for (auto& x: objects)
			x->move(speed * dx[0], speed * dy[0]);
	for (auto& x: objects)
		if (x->getY() >= coord.getY() + fullWidth)
			x->getY() -= fullWidth;
		else if (x->getY() + x->getWidth() - 1 < coord.getY())
			x->getY() += fullWidth;
	trafficLight->update();
}
void Lane::add(Object* obj, int safeDistance = 4) {
	fullWidth += safeDistance;
	obj->getY() = coord.getY() + fullWidth;
	fullWidth += obj->getWidth();
	obj->getX() = coord.getX();
	objects.push_back(obj);
}
void Lane::draw() {
	for (auto& x: objects)
		x->draw();
}
void Lane::reset() {
	if (objects.empty())
		return;
	double dy = objects[0]->getY();
	for (auto& x: objects) {
		x->getY() -= dy;
		if (x->getY() + x->getWidth() - 1 < 0)
			x->getY() += fullWidth;
		else if (x->getY() >= fullWidth)
			x->getY() -= fullWidth;
	}
	trafficLight->reset();
}
int Lane::getHeight() {
	int res = 0;
	for (auto& x: objects)
		res = max(res, x->getHeight());
	return res;
}
void Lane::save(XMLDocument* doc, XMLElement* root, int id = 0) {
	XMLElement* lane = doc->NewElement("lane");
	
	lane->SetAttribute("id", id);
	lane->SetAttribute("coordX", coord.getX());
	lane->SetAttribute("coordY", coord.getY());
	lane->SetAttribute("speed", speed);
	lane->SetAttribute("fullWidth", fullWidth);
	trafficLight->save(doc, lane);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->save(doc, lane, i);

	root->InsertEndChild(lane);
}
void Lane::load(XMLElement* lane) {
	cerr << "loading a lane\n";
	clear();
	lane->QueryIntAttribute("coordX", &coord.getX());
	lane->QueryIntAttribute("coordY", &coord.getY());
	lane->QueryDoubleAttribute("speed", &speed);
	lane->QueryIntAttribute("fullWidth", &fullWidth);

	trafficLight = new TrafficLight;
	trafficLight->load(lane);

	XMLElement* objNode = lane->FirstChildElement("Object");
	while (objNode) {
		Object* obj = Obstacle::_load(window, objNode);
		objects.push_back(obj);
		objNode = objNode->NextSibling();
	}
	cerr << "a lane loaded\n";
}