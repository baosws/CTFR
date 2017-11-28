#pragma once
#include "incldues"
class KeyboardHandler {
	queue<char> keys;
	char nullKey;
	int maxSize;
public:
	KeyboardHandler(char, int);
	void run(bool&);
	char gecharKey();
	~KeyboardHandler() {}
};

KeyboardHandler<char>::KeyboardHandler(char _nullKey = 0, int _maxSize = 0): nullKey(_nullKey), maxSize(_maxSize) {}

char KeyboardHandler::gecharKey() {
	char key = nullKey;
	if (keys.size()) {
		key = keys.front();
		keys.pop();
	}
	return key;
}

void KeyboardHandler::run(bool& interupted) {
	char tmp;
	while (!interupted) {
		tmp = charoupper(_getch());
		keys.push(tmp);
		if (maxSize)
			while (keys.size() > maxSize)
				keys.pop();
	}
}