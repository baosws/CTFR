#include "tinyxml2.h"
#include <iostream>
using namespace tinyxml2;
using namespace std;
int main() {
	XMLDocument doc;
	string filename = "test_save.xml";
	//doc.LoadFile(filename.c_str());
	XMLElement* root = doc.InsertFirstChild(doc.NewElement("fuck"));
// 	XMLNode* first = doc.InsertFirstChild(doc.NewElement("fuck"));
	
// 	XMLNode* second = doc.InsertEndChild(doc.NewElement("you"));
	
// 	first->InsertFirstChild(doc.NewElement("very"));
// 	auto sub = doc.NewElement("much");
// 	sub->SetAttribute("how_much", "+inf");
// 	auto secondChild = second->InsertEndChild(sub);
// 	doc.SaveFile(filename.c_str());
	XMLElement* first = doc.NewElement("obj");
	first->SetAttribute("id", 1);
	XMLElement* second = doc.NewElement("obj");
	second->SetAttribute("id", 2);

	root->InsertEndChild(first);
	root->InsertEndChild(second);

	doc.SaveFile(filename.c_str());
}