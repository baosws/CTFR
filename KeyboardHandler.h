#pragma once
#include "includes.h"
class KeyboardHandler {
	queue<char> keys; // save
	char nullKey; // save
	int maxSize; // save
public:
	KeyboardHandler(char, int);
	void run(int&);
	char getKey();
	void reset();
	~KeyboardHandler() {}
};

KeyboardHandler::KeyboardHandler(char _nullKey = 0, int _maxSize = 0): nullKey(_nullKey), maxSize(_maxSize) {}

char KeyboardHandler::getKey() {
	char key = nullKey;
	if (keys.size()) {
		key = keys.front();
		keys.pop();
	}
	return key;
}
void KeyboardHandler::reset() {
	while (keys.size())
		keys.pop();
}
void KeyboardHandler::run(int& state) {
	char tmp;
	while (state) {
		//while (1);
		tmp = toupper(_getch());
		keys.push(tmp);
		if (maxSize)
			while (keys.size() > maxSize)
				keys.pop();
	}
}