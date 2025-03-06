#include "game.h"
#include <ctime>

int main() {
	srand(time(NULL));
	Game game;
	game.play();

	return 0;
}