#pragma once
#include "includes.h"
class Dialog {
protected:
	Window* window;
	Point coord;
	vector<string>* contents;
public:
	static vector<string> DefaultContents[];
	Dialog(Window*, int, int, int);
	~Dialog() {}
	void draw(Window*);
};
Dialog::Dialog(Window* w, int x, int y, int type) {
	window = w;
	coord = Point(x, y);
	contents = &Dialog::DefaultContents[type];
}
void Dialog::draw(Window* w = NULL) {
	if (!w)
		w = window;
	for (int i = 0; i < contents->size(); i++)
		w->putStringXY(coord.getX() - contents->size() + i, coord.getY() - (*contents)[i].length() / 2, (*contents)[i], 10);
}
vector<string> Dialog::DefaultContents[] = {
	{"~~~GAME OVER~~~", "----RESTART? [Y]es/[N]o----"},
	{"----WELCOME TO \"CROSS THE F*****G ROAD----\"", "[1]. Start New Game", "[2]. Load Saved Game", "[3]. Exit"}
};