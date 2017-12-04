#pragma once
#include "../includes.h"

class Game {
	Window* window; // not save
	Map* map; // save
	int state = RUNNING; // save
	KeyboardHandler* keyBoardHandler = new KeyboardHandler('\0', 4); // not save
	thread keyboard = thread([&] {keyBoardHandler->run();} ); // not save
	void save(XMLDocument*, XMLElement*);
	void load(XMLElement*);
	void loadGameF(string);
	void process();
public:
	Game();
	~Game();
	bool isRunning();
	void startGame();
	void pauseGame();
	void resumeGame();
	void exitGame();
	void resetGame();
	void saveGame();
	void loadGame();
	void setting();
	void run();
};
typedef void (Game::*Command)();
Game::Game() {
	window = new Window();
	window->setTitle("LOADING DATA");
	Dialog loading(window);
	loading.addContent("Loading data...");
	loading.show();
	Sleep(LOADING_DATA);
	map = new Map(window);
	window->clearScreen();
}
Game::~Game() {
	keyBoardHandler->exit();
	keyboard.join();
	delete keyBoardHandler;
	if (window)
		delete window;
	if (map)
		delete map;
}

bool Game::isRunning() {
	return state & RUNNING;
}
void Game::pauseGame() {
	window->setTitle("PAUSE GAME");
	map->pause();
	state &= ~PLAYING;
}
void Game::resumeGame() {
	window->setTitle("RESUME GAME");
	map->resume();
	state |= PLAYING;
}
void Game::exitGame() {
	window->setTitle("EXIT GAME");
	state = 0;
	Sleep(WAIT_FOR_THREAD_TO_TERMINATE);
}
void Game::resetGame() {
	window->setTitle("WAITING");
	state = RUNNING;
	window->clearScreen(true);
	map->reset();
	keyBoardHandler->reset();
}
void Game::saveGame() {
	window->setTitle("SAVE GAME");
	state = PLAYING;
	Sleep(WAIT_FOR_THREAD_TO_TERMINATE);

	Prompt p;
	string filename = p.show(window, keyBoardHandler, "Input file name to save: ");
	filename += ".xml";
	
	XMLDocument* doc = new XMLDocument;
	XMLElement* root = doc->InsertFirstChild(doc->NewElement("root"));
	save(doc, root);
	doc->SaveFile(filename.c_str());

	delete doc;
	loadGameF(filename);
}
void Game::loadGameF(string filename) {
	XMLDocument* doc = new XMLDocument;
	doc->LoadFile(filename.c_str());
	XMLElement* root = doc->FirstChildElement();
	load(root);
	delete doc;
	MenuHandler afterSaving(window, keyBoardHandler, "Keep playing?", {
		{"Yeah maybe", startGame},
		{"No thanks", exitGame}
	});
	(this->*(afterSaving.run()))();
}
void Game::loadGame() {
	window->setTitle("LOAD GAME");
	state = PLAYING;
	Sleep(WAIT_FOR_THREAD_TO_TERMINATE);
	
	Prompt p;
	string filename = p.show(window, keyBoardHandler, "Input file name to load: ");
	filename += ".xml";
	
	XMLDocument* doc = new XMLDocument;
	
	while (doc->LoadFile(filename.c_str())) {
		filename = p.show(window, keyBoardHandler, "File not available, please input file name to load again: ");
		filename += ".xml";
	}
	load(doc->FirstChildElement());
	delete doc;
	startGame();
}
void Game::setting() {
	exitGame();
	window->setTitle("SETTING");
	Prompt p;
	string level = p.show(window, keyBoardHandler, "Choose level (0 -> " + to_string(Map::MaxLevel()) + "): ");
	map->setLevel(to_num(level));
}
void Game::run() {
	MenuHandler menu(window, keyBoardHandler, "Welcome to CROSS THE FURY ROAD!!!", {
		{" Start new game", startGame},
		{"Load saved game", loadGame},
		{"        Setting", setting},
		{"      Exit game", exitGame}
	});
	while (1) {
		resetGame();
		auto cmd = menu.run();
		(this->*cmd)();
		if (cmd == &exitGame)
			return;
		while (state);
	}
}
void Game::process() {
	MenuHandler gameOverHandler(window, keyBoardHandler, "GAME OVER!!!! RESTART???", {
				{"Yeah maybe", startGame},
				{"Nah thanks", exitGame}
			});
	while (isRunning()) {
		map->run();
		if (map->gameOver()) {
			state = PLAYING;
			auto cmd = gameOverHandler.run();
			resetGame();
			(this->*cmd)();
			continue;
		}
		window->setTitle(("Level: " + to_string(map->getLevel())).c_str());
		window->render();
	}
}
void Game::startGame() {
	state |= RUNNING;
	thread gameProcessor([&] {process();});
	while (isRunning()) {
		char tmp = keyBoardHandler->getKey();
		if (!map->gameOver()) {
			if (tmp == 27)
				exitGame();
			else if (tmp == PAUSE_KEY)
				pauseGame();
			else if (tmp == RESUME_KEY)
				resumeGame();
			else if (tmp == SAVE_KEY)
				saveGame();
			else if (tmp == LOAD_KEY)
				loadGame();
			else {
				tmp = string("AWDS").find(tmp);
				int dir = (tmp != string::npos) ? tmp : -1;
				map->setPlayerDir(dir);
			}
		}
	}
	gameProcessor.join();
}
void Game::save(XMLDocument* doc, XMLElement* root) {
	XMLElement* game = doc->NewElement("game");
	game->SetAttribute("state", state);
	map->save(doc, game);

	root->InsertEndChild(game);
}
void Game::load(XMLElement* root) {
	cerr << "loading game\n";
	XMLElement* game = root->FirstChildElement("game");
	game->QueryIntAttribute("state", &state);
	map->load(game);
	cerr << "game loaded\n";
}