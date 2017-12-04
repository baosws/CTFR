#pragma once
#include "../includes.h"
class Prompt {
public:
	string show(Window*, KeyboardHandler*, string);
};
string Prompt::show(Window* w, KeyboardHandler* kb, string cap) {
	w->clearScreen();
	w->gotoXY(w->getX(), w->getY());
	cout << cap;
	string s;
	kb->reset();
	int l = 1;
	while (1) {
		char tmp = kb->getKey();
		if (tmp == ENTER_KEY)
			break;
		if (tmp) {
			if (tmp != BACKSPACE_KEY) {
				s += tmp;
				w->_putCharXY(w->getX(), cap.length() + l++, tmp);
			} else {
				w->_putCharXY(w->getX(), cap.length() + --l, ' ');
				s.erase(s.length() - 1, 1);
			}
		}
		w->render();

	}
	w->clearScreen(true);
	kb->resume();
	return s;
}