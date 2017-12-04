#pragma once
#include "../includes.h"
class Game; // prototype
typedef void (Game::*Command)();
class MenuHandler {
	Window* window;
	Dialog dialog;
	KeyboardHandler* kb;
	vector<Command> commands;
public:
	MenuHandler(Window*, KeyboardHandler*, string, vector<pair<string, Command> >);
	// ~MenuHandler();

	Command run();
};
MenuHandler::MenuHandler(Window* w, KeyboardHandler* _kb, string title, vector<pair<string, Command> > choices): dialog(w) {
	window = w;
	kb = _kb;
	dialog.addContent(title);
	for (int i = 1; i <= choices.size(); i++)
		dialog.addContent("[" + to_string(i) + "]. " + choices[i - 1].first);
	for (auto& x: choices)
		commands.push_back(x.second);
	//cerr << "MenuHandler created\n";
}
Command MenuHandler::run() {
	dialog.show();
	kb->reset();
	int t;
	while (1) {
		t = kb->getKey() - '0';
		if (t >= 1 && t <= commands.size())
			break;
	}
	return commands[t - 1];
}