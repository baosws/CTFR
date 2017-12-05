#pragma once
#include "../includes.h"
class Player: public Object {
	int dead = false; // save
	int curDir = -1; // save
public:
	Player(Window*);
	~Player() {}
	void move(double, double);
	void setDir(int);
	void moveByCurDir();
	bool isFinished();
	bool isDead();
	void die();
	void reset();
	void save(XMLDocument* doc, XMLElement* root);
	void load(XMLElement* root);
};

Player::Player(Window* w = NULL): Object(w) {
	if (w)
		coord = PointF(w->getHeight() - getHeight(), w->getWidth() / 2 - 1);
}
bool Player::isFinished() {
	return coord.getX() == 0;
}
void Player::die() {
	dead = true;
}
void Player::reset() {
	dead = false;
	curDir = -1;
	coord = PointF(window->getHeight() - 1, window->getWidth() / 2 - 1);
}
bool Player::isDead() {
	return dead;
}
void Player::setDir(int dir) {
	if (curDir == -1 && dir != -1)
		curDir = dir;
}
void Player::moveByCurDir() {
	if (curDir != -1)
		move(dx[curDir], dy[curDir]);
	curDir = -1;
	draw();
}
void Player::move(double dx, double dy) {
	Object::move(dx, dy);
	//cerr << getX() << "" << getY() << "\t" << window->getHeight() << " " << window->getWidth() << endl;
	if (   getX() < 0
		|| getX() + getHeight() - 1 >= window->getHeight()
		|| getY() < 0
		|| getY() + getWidth() - 1 >= window->getWidth())
			Object::move(-dx, -dy);
}
void Player::save(XMLDocument* doc, XMLElement* root) {
	XMLElement* player = doc->NewElement("player");
	player->SetAttribute("coordX", coord.getX());
	player->SetAttribute("coordY", coord.getY());
	player->SetAttribute("dead", dead);
	player->SetAttribute("curDir", curDir);
	
	root->InsertEndChild(player);
}
void Player::load(XMLElement* root) {
	cerr << "loading player\n";
	XMLElement* player = root->FirstChildElement("player");
	player->QueryDoubleAttribute("coordX", &coord.getX());
	player->QueryDoubleAttribute("coordY", &coord.getY());
	player->QueryIntAttribute("dead", &dead);
	player->QueryIntAttribute("curDir", &curDir);
	cerr << "player loaded\n";
}