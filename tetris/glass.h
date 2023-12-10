////////////////////////////////////////////////
//
//	Program tetris, glass.h
//
//	Simple tetris in console
// 
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////
#pragma once

#ifndef GLASS_H
#define GLASS_H

#include "main.h"

class Glass {
public:
	Glass();
	~Glass();

	uint8_t Reset();
	uint8_t Randomize();
	uint8_t Check();

	std::vector <std::vector <uint8_t>> GetGlass() { return _cell; }
	uint8_t PutCell(uint8_t x, uint8_t y) {this->_cell[x][y] = 1; return 0; }
private:
	std::vector <std::vector <uint8_t>> _cell = std::vector <std::vector <uint8_t>>(BD_GLASS__HEIGHT, std::vector <uint8_t>(BD_GLASS__WIDTH, 0));
};

#endif // !GLASS_H