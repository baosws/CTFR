#pragma once
#include "includes.h"
const int RUNNING = 1;
const int PLAYING = 2;
class Game {
	Window* window; // not save
	Map* map; // save
	int state = RUNNING; // save
	KeyboardHandler keyBoardHandler = KeyboardHandler('\0', 4); // not save
	thread keyboard = thread([&] {keyBoardHandler.run(state);} ); // not save
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
	void run();
	void process();
};
typedef void (Game::*Command)();
Game::Game() {
	window = new Window();
	map = new Map(window);
}
Game::~Game() {
	keyboard.join();
	delete window;
	delete map;
}
bool Game::isRunning() {
	return state & 1;
}
void Game::pauseGame() {
	map->pause();
	state &= ~PLAYING;
}
void Game::resumeGame() {
	map->resume();
	state |= PLAYING;
}
void Game::exitGame() {
	state = 0;
}
void Game::resetGame() {
	state = RUNNING;
	window->clearScreen(true);
	map->reset();
	keyBoardHandler.reset();
}
void Game::saveGame() {}
void Game::loadGame() {}

void Game::run() {
	MenuHandler menu(window, &keyBoardHandler, "Welcome to CROSS THE FUCKING ROAD!!!", {
		{"Start new game", startGame},
		{"Load saved game", loadGame},
		{"Exit game", exitGame}
	});
	bool started = false;
	while (1) {
		resetGame();
		cerr << "runned" << endl;
		auto cmd = menu.run();
		(this->*cmd)();
		if (cmd == &exitGame)
			return;
		while (state);
	}
}
void Game::process() {
	MenuHandler gameOverHandler(window, &keyBoardHandler, "GAME OVER! U SUCK!!! FUCK U!!! RESTART?", {
				{"Fuck yeah", resetGame},
				{"Fuck no", exitGame}
			});
	while (isRunning()) {
		map->run();
		if (map->gameOver()) {
			auto cmd = gameOverHandler.run();
			(this->*cmd)();
			continue;
		}
		window->setTitle(("Score: " + to_string(map->getLevel())).c_str());
		window->render();
	}
}
void Game::startGame() {
	resetGame();
	thread gameProcessor([&] {process();});
	while (isRunning()) {
		char tmp = keyBoardHandler.getKey();
		cerr << tmp << endl;
		if (map->gameOver()) {
			if (tmp == 'Y')
				resetGame();
			else if (tmp == 'N')
				exitGame();
		}
		else {
			if (tmp == 27)
				exitGame();
			else if (tmp == 'P')
				pauseGame();
			else if (tmp == 'C')
				resumeGame();
			else {
				tmp = string("AWDS").find(tmp);
				int dir = (tmp != string::npos) ? tmp : -1;
				map->setPlayerDir(dir);
			}
		}
	}
	gameProcessor.join();
}