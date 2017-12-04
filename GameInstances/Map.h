#pragma once
#include "../includes.h"
const int MAX_SPEED = 35;
const int d_LEVEL = 5;
class Map {
	Window* window; // not save
	Player* player; // save
	
	Road* road; // save

	int level; // save
	int isRunning; // save
	int defaultLevel = 0;
	void initialLevel();
public:
	Map(Window*);
	~Map();
	void reset(bool);
	void pause();
	void resume();
	void setLevel(int);
	void run();

	bool gameOver();
	int getLevel();
	void setPlayerDir(int);
	
	void save(XMLDocument* doc, XMLElement* root);
	void load(XMLElement* root);
};

Map::Map(Window* w = NULL) {
	if (!w)
		return;
	window = w;
	player = new Player(w);
	road = new Road(w);
	isRunning = true;
	level = 0;
	initialLevel();
}
Map::~Map() {
	delete player;
	delete road;
}
void Map::setLevel(int lev) {
	defaultLevel = lev * d_LEVEL % MAX_SPEED;
	reset(false);
}
void Map::initialLevel() {
	// addlane(safeDistX, safeDistY, count, speed, y = 0)
	road->addLane<Bird>(0, 10, 15, -0.2);
	road->addLane<Plane>(0, 15, 6, 0.8);
	road->addLane<Car>(0, 10, 8, -0.4);
	road->addLane<Truck>(0, 15, 6, 0.4);
	road->addLane<Bird>(0, 10, 15, -0.5);
	road->addLane<Snake>(0, 7, 5, 0.4);
}
void Map::reset(bool levelUp = false) {
	isRunning = true;
	level = (level + d_LEVEL) % MAX_SPEED;
	player->reset();
	road->reset();
	if (!levelUp)
		level = defaultLevel;
}
void Map::pause() {
	isRunning = false;
}
void Map::resume() {
	isRunning = true;
}
void Map::run() {
	auto delayTime = [&] {return MAX_SPEED - level;};
	if (isRunning) {
		if (player->isDead() || road->crash(player))
			player->die();
		else {
			if (player->isFinished()) {
				reset(true); // level-up
				Dialog levelUp(window);
				int nextLevel = getLevel();
				if (nextLevel)
					levelUp.addContent("LEVEL UP TO LEVEL " + to_string(nextLevel) + "!!!");
				else
					levelUp.addContent("RETURNING TO LEVEL 0!!!");
				levelUp.show();
				Sleep(LEVEL_UP);
			}
			else {
				player->moveByCurDir();
				road->run();
			}
		}
		Sleep(delayTime());
	}
}
bool Map::gameOver() {
	return player->isDead();
}
int Map::getLevel() {
	return level / d_LEVEL;
}
void Map::setPlayerDir(int dir) {
	player->setDir(dir);
}
void Map::save(XMLDocument* doc, XMLElement* root) {
	XMLElement* map = doc->NewElement("map");

	map->SetAttribute("level", level);
	map->SetAttribute("isRunning", isRunning);
	player->save(doc, map);
	road->save(doc, map);

	root->InsertEndChild(map);
}
void Map::load(XMLElement* root) {
	cerr << "loading map\n";
	XMLElement* map = root->FirstChildElement("map");
	
	map->QueryIntAttribute("level", &level);
	map->QueryIntAttribute("isRunning", &isRunning);
	player->load(map);
	road->load(map);
	cerr << "map loaded\n";
}