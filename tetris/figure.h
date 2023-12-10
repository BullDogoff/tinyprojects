////////////////////////////////////////////////
//
//	Program tetris, figure.h
//
//	Simple tetris in console
// 
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////
#pragma once

#ifndef FIGURE_H
#define FIGURE_H

#include "main.h"

struct Cell {
	Cell(int x = 0, int y = 0) : X(x), Y(y) {}

	int8_t X = 0;
	int8_t Y = 0;
};

const std::array <Cell, 4> q0{ Cell(0, 0), Cell(0, 1), Cell(-1, 0), Cell(-1, 1) };
const std::array <Cell, 4> q1{ Cell(1, 0), Cell(0, 0), Cell(0, 1), Cell(-1, 0) };
const std::array <Cell, 4> q2{ Cell(1, 0), Cell(0, 0), Cell(-1, 0), Cell(-1, 1) };
const std::array <Cell, 4> q3{ Cell(1, 0), Cell(0, 0), Cell(-1, 0), Cell(-1, -1) };
const std::array <Cell, 4> q4{ Cell(1, 0), Cell(0, 0), Cell(-1, 0), Cell(-2, 0) };

const std::map <uint8_t, std::array <Cell, 4>> figureDictionary = {
	{0, {q0[0], q0[1], q0[2], q0[3]}},
	{1, {q1[0], q1[1], q1[2], q1[3]}},
	{2, {q2[0], q2[1], q2[2], q2[3]}},
	{3, {q3[0], q3[1], q3[2], q3[3]}},
	{4, {q4[0], q4[1], q4[2], q4[3]}}
};

class Figure {
public:
	Figure();
	~Figure();

	uint8_t Generate();
	std::vector <Cell> GetCoordinates();
	std::pair <uint8_t, uint8_t> GetPosition() {return std::pair <uint8_t, uint8_t> (_positionX, _positionY);}
	const bool IsActive() {return this->_active;}
	uint8_t Switch() {this->_active = !this->_active; return 0;}

	uint8_t MoveDown(uint8_t);
	uint8_t MoveRight();
	uint8_t MoveLeft();
	uint8_t Rotate();

	uint8_t Move(uint8_t dir, uint8_t dist = 1);
private:
	uint8_t _positionX, _positionY;
	Cell _cell[4];

	bool _active;
};

#endif // !FIGURE_H