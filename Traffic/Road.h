#pragma once
#include "../includes.h"
class Road {
	Window* window;
	vector<Lane*> lanes; // save
public:
	Road(Window*);
	~Road();

	template<class T>
	void addLane(int, int, int, double, int);

	void run();
	bool crash(Player*);
	void reset();
	void clear() {
		for (auto& x: lanes)
			delete x;
		lanes.clear();
	}
	void save(XMLDocument* doc, XMLElement* root, int id = 0);
	void load(XMLElement* root);
};

Road::Road(Window* w = NULL) {
	if (!w)
		return;
	lanes.clear();
	window = w;
	srand(time(NULL));
}
Road::~Road() {
	clear();
}

void Road::run() {
	for (auto& x: lanes)
		x->run();
	for (auto& x: lanes)
		x->draw();
}
void Road::reset() {
	for (auto& x: lanes)
		x->reset();
}
bool Road::crash(Player* player) {
	for (auto& x: lanes)
		if (x->crash(player))
			return true;
	return false;
}
template<class T>
void Road::addLane(int safeDistX, int safeDistY, int count, double speed, int y = 0) {
	int last = 0;
	if (lanes.size())
		last = lanes.back()->getX() + lanes.back()->getHeight();
	Lane* newLane = new Lane(window, last + safeDistX, y, speed);
	while (count--)
		newLane->add(new T(window), safeDistY);
	lanes.push_back(newLane);
}
void Road::save(XMLDocument* doc, XMLElement* root, int id = 0) {
	XMLElement* road = doc->NewElement("road");

	road->SetAttribute("id", id);
	for (int i = 0; i < lanes.size(); i++)
		lanes[i]->save(doc, road, i);

	root->InsertEndChild(road);
}
void Road::load(XMLElement* root) {
	cerr << "loading road\n";
	clear();
	XMLElement* road = root->FirstChildElement("road");

	XMLElement* laneNode = road->FirstChildElement();
	while (laneNode) {
		Lane* lane = new Lane(window);
		lane->load(laneNode);
		lanes.push_back(lane);
		laneNode = laneNode->NextSibling();
	}
	cerr << "road loaded\n";
}