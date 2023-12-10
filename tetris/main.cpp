////////////////////////////////////////////////
//
//	Program tetris, main.cpp
//
//	Simple tetris in console
//
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////

#include "program.h"

int main() {
	Game game;

	std::cout.setf(std::ios::fixed);
	std::cout.precision(8);

	while (game.IsRunning()) {
		game.DoStep();
	}

	return 0;
}