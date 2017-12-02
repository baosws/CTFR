#pragma once
#include "includes.h"
const int MAX_SPEED = 20ll;
const int d_LEVEL = 5;
class Map {
	Window* window; // not save
	Player* player; // save
	Road* road; // save
	int level; // save
	bool isRunning; // save
	void initialLevel();
public:
	Map(Window*);
	~Map();
	void reset(bool);
	void pause();
	void resume();

	void run();

	bool gameOver();
	int getLevel();
	void setPlayerDir(int);
	
	friend class Game;
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
void Map::initialLevel() {
	// addlane(safeDistX, safeDistY, count, speed, y = 0)
	road->addLane<Bird>(1, 10, 15, -0.2);
	road->addLane<Plane>(1, 15, 6, 0.8);
	road->addLane<Car>(1, 10, 8, -0.4);
	road->addLane<Truck>(1, 15, 6, 0.4);
	road->addLane<Bird>(1, 10, 15, -0.5);
	road->addLane<Snake>(1, 7, 5, 0.4);
}
void Map::reset(bool levelUp = false) {
	isRunning = true;
	level = (level + d_LEVEL) % MAX_SPEED;
	player->reset();
	road->reset();
	if (!levelUp)
		level = 0;
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
			if (player->isFinished())
				reset(true); // level-up
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