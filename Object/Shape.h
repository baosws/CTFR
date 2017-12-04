#pragma once
#include "../includes.h"
typedef vector<string> MyShape;
class Shape {
	MyShape base; // save
public:
	Shape(MyShape);
	Shape();
	int getWidth() const;
	int getHeight() const;
	~Shape();
	void draw(int, int, Window*) const;
	bool isNullCell(int, int) const;
};

Shape::Shape(MyShape a) {
	base = a;
}
void Shape::draw(int x, int y, Window* w) const {
	for (int i = 0; i < base.size(); i++)
		for (int j = 0; j < base[i].length(); j++)
			if (base[i][j] != ' ')
				w->putCharXY(x + i, y + j, base[i][j]);
}
Shape::~Shape() {}
int Shape::getWidth() const {
	int m = 0;
	for (int i = 0; i < base.size(); i++)
		m = max(m, (int)base[i].length());
	return m;
}
int Shape::getHeight() const {
	return base.size();
}
bool Shape::isNullCell(int i, int j) const {
	//cerr << i << " " << j << " " << endl;
	if (i < 0 || i >= getHeight())
		return true;
	if (j < 0 || j >= base[i].length())
		return true;
	//cerr << base[i][j] << endl;
	return base[i][j] == ' ';
}
const Shape Shapes[] = {
					Shape({"\2"}), // people
					Shape({"  **** ",
						   "**O**O**"}), // car
					Shape({"__  __",
						   "  \\/"}), // bird
					Shape({"   /",
						   "  /   /",
						   "<====<",
						   "  \\   \\",
						   "   \\"}), // plane
					Shape({"  **  ******",
						   "<***********",
						   "<.o.....O.O."}), // truck
					Shape({"**",
						   "**",
						   "  ****",
						   " * **",
						   "   *"}), // duck
					Shape({"Oooooooooooooooooooooooooooooooo.."}), // loooooooooooooooong snake
					Shape({"+"}), // red light
					Shape({"-"}) // green light
				};