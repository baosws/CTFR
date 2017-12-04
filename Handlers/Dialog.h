#pragma once
#include "../includes.h"
typedef vector<string> Contents;
class Dialog {
protected:
	Window* window;
	Point coord; // not save
	Contents contents; // not save
public:
	Dialog(Window*);
	void addContent(string);
	~Dialog() {}
	void show();
};
Dialog::Dialog(Window* w = NULL) {
	window = w;
	if (w)
		coord = Point(w->getX() + w->getHeight() / 2, w->getY() + w->getWidth() / 2);
}
void Dialog::addContent(string content) {
	contents.push_back(content);
}
void Dialog::show() {
	for (int i = 0; i < contents.size(); i++)
		window->putStringXY(coord.getX() - contents.size() + i, coord.getY() - contents[i].length() / 2, contents[i], 10);
	window->render();
}