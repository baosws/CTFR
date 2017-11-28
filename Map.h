#pragma once
#include "includes.h"
const int MAX_SPEED = 20ll;
const int d_LEVEL = 5;
class Map {
	Window* window;
	People* player;
	Road* road;
	int level;
	int delayTime();
	bool crash();
	bool isRunning;
	void initialLevel();
	void draw();
public:
	Map(Window*);
	~Map();
	void reset(bool);
	void pause();
	void resume();
	void run(int&);
	bool gameOver();
	int getLevel();
};

Map::Map(Window* w) {
	isRunning = true;
	window = w;
	level = 0;
	player = new People(window, w->getHeight() - 1, w->getWidth() / 2);
	road = new Road(window);
	initialLevel();
}
Map::~Map() {
	delete player;
	delete road;
}
void Map::initialLevel() {
	// addlane(safeDistX, safeDistY, count, speed, y = 0)
	road->addLane<Bird>(1, 10, 15, -0.5);
	road->addLane<Plane>(1, 15, 6, 0.8);
	road->addLane<Car>(1, 10, 8, -0.4);
	road->addLane<Truck>(1, 15, 6, 0.4);
	road->addLane<Bird>(1, 10, 15, -0.5);
	road->addLane<Snake>(1, 7, 5, 0.4);
}
bool Map::crash() {
	return road->crash(player);
}
int Map::delayTime() {
	return MAX_SPEED - level;
}
void Map::reset(bool levelUp = false) {
	isRunning = true;
	level = (level + d_LEVEL) % MAX_SPEED;
	window->clearScreen(true);
	*player = People(window, window->getHeight() - 1, window->getWidth() / 2);
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
void Map::run(int& dir) {
	if (isRunning) {
		if (player->isDead() || crash()) {
			player->die();
		}
		else {
			if (dir) {
				player->move(dir - 1);
				dir = 0;
			}
			road->run();
			if (player->isFinish(window->coord.getX()))
				reset(true); // level-up
		}
		draw();
		Sleep(delayTime());
	}
}
void Map::draw() {
	player->draw();
	road->draw();
}
bool Map::gameOver() {
	return player->isDead();
}
int Map::getLevel() {
	return level / d_LEVEL;
}