#pragma once
#include "includes.h"
typedef vector<string> MyShape;
class Shape {
	MyShape base;
	bool overlap;
public:
	static Shape DefaultShape[];
	Shape(vector<string>, bool);
	int getWidth();
	int getHeight();
	~Shape();
	void draw(int, int, const Window*) const;
	bool isNullCell(int, int);
};

Shape::Shape(MyShape a, bool overlap = false) {
	base = a;
}
void Shape::draw(int x, int y, const Window* w) const {
	for (int i = 0; i < base.size(); i++)
		for (int j = 0; j < base[i].length(); j++)
			if (base[i][j] != ' ' || overlap)
				w->putCharXY(x + i, y + j, base[i][j]);
}
Shape::~Shape() {}
int Shape::getWidth() {
	int m = 0;
	for (int i = 0; i < base.size(); i++)
		m = max(m, (int)base[i].length());
	return m;
}
int Shape::getHeight() {
	return base.size();
}
bool Shape::isNullCell(int i, int j) {
	//cerr << i << " " << j << " " << endl;
	if (i < 0 || i >= getHeight())
		return true;
	if (j < 0 || j >= base[i].length())
		return true;
	//cerr << base[i][j] << endl;
	return base[i][j] == ' ';
}
Shape Shape::DefaultShape[] = {
							Shape({"X"}), // people
							Shape({"  ***  ", "**@*@**"}), // car
							Shape({"_   _", " \\./"}), // bird
							Shape({"   /", "  /   /", "<****<", "  \\   \\", "   \\"}), // plane
							Shape({"  **  ******",
								   "************",
								   "**@*****@*@*"}), // truck
							Shape({"**",
								   "**",
								   "  ****",
								   " * **",
								   "   *"}), // duck
							Shape({"OOooooooooooooooooo.."}) // snake
						};