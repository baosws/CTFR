#pragma once
#include "../includes.h"
class KeyboardHandler {
	queue<char> keys; // save
	char nullKey; // save
	int maxSize; // save
	int state = 0;
public:
	KeyboardHandler(char, int);
	void run();
	char getKey();
	void reset();
	void pause();
	void resume();
	void exit();
	~KeyboardHandler() {}
};

KeyboardHandler::KeyboardHandler(char _nullKey = 0, int _maxSize = 0): nullKey(_nullKey), maxSize(_maxSize) {}

char KeyboardHandler::getKey() {
	char key = nullKey;
	if (keys.size() && state & PLAYING) {
		key = keys.front();
		keys.pop();
	}
	return key;
}
void KeyboardHandler::reset() {
	state = RUNNING | PLAYING;
	while (keys.size())
		keys.pop();
}
void KeyboardHandler::pause() {
	state &= ~PLAYING;
}
void KeyboardHandler::resume() {
	state |= PLAYING;
}
void KeyboardHandler::exit() {
	state = 0;
}
void KeyboardHandler::run() {
	state = RUNNING | PLAYING;
	char tmp;
	while (state & RUNNING)
	if (state & PLAYING) {
		tmp = toupper(_getch());
		keys.push(tmp);
		if (maxSize)
			while (keys.size() > maxSize)
				keys.pop();
	}
}