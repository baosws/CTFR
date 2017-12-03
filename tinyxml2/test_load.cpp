#include "tinyxml2.h"
#include <iostream>
using namespace tinyxml2;
using namespace std;
int maixn() {
	XMLDocument doc;
	doc.LoadFile("test.xml");
	XMLElement* root = doc.RootElement();

	XMLElement* child1 = root->FirstChildElement();
	double team;
	child1->QueryDoubleAttribute("team", &team);
	cout << team;
}