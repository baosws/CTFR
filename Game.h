#pragma once
#include "includes.h"
class Game {
	Window* window;
	Map* map;
	Dialog* gameOverDialog;
	Dialog* menuDialog;
public:
	Game();
	~Game();
	void startGame();
	void pauseGame();
	void resumeGame();
};

Game::Game() {
	window = new Window();
	gameOverDialog = new Dialog(window, window->getHeight() / 2, window->getWidth() / 2, 0);
	menuDialog = new Dialog(window, window->getHeight() / 2, window->getWidth() / 2, 1);
	map = new Map(window);
}
Game::~Game() {
	delete window;
	delete gameOverDialog;
	delete menuDialog;
	delete map;
}
void Game::pauseGame() {
	map->pause();
}
void Game::resumeGame() {
	map->resume();
}
void Game::startGame() {
	int dir = 0;
	bool exited = false;
	auto exitGame = [&] {exited = true;};
	queue<char> keys;
	auto resetGame = [&] {
		window->clearScreen(true);
		map->reset();
		dir = 0;
		while (keys.size())
			keys.pop();
	};
	resetGame();
	menuDialog->draw();
	window->render();
	thread keyBoardHandler([&] {
		while (!exited) {
			char tmp;
			tmp = toupper(_getch());
			keys.push(tmp);
			while (keys.size() > 4)
				keys.pop();
		}
	});
	while (!exited) {
		if (keys.empty())
			continue;
		char tmp = keys.front();
		keys.pop();
		if (tmp == '1')
			break;
		else if (tmp == '2')
			continue;
		else if (tmp == '3')
			exitGame();
	}
	thread gameProcessor([&] {
		while (!exited) {
			map->run(dir);
			if (map->gameOver()) {
				gameOverDialog->draw();
				window->render();
				while (!exited && map->gameOver());
			}
			window->setTitle(("Score: " + to_string(map->getLevel())).c_str());
			window->render();
		}
	});
	while (!exited) {
		if (keys.empty())
			continue;
		char tmp = keys.front();
		keys.pop();
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
				dir = (tmp != string::npos) ? tmp + 1 : 0;
			}
		}
	}
	keyBoardHandler.join();
	gameProcessor.join();
}