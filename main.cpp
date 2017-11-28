#include "includes.h"
int main() {
	freopen("err.out", "w", stderr);
	// ios::sync_with_stdio(false);
	Game* game = new Game;
	game->startGame();
	delete game;
}