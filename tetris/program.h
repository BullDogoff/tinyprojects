////////////////////////////////////////////////
//
//	Program tetris, program.h
//
//	Simple tetris in console
// 
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////
#pragma once

#ifndef PROGRAM_H
#define PROGRAM_H

#include "main.h"
#include "program.h"
#include "glass.h"
#include "figure.h"


class Game {
public:
	Game();
	~Game();

	uint8_t DoStep();
	uint8_t Redraw();

	bool IsRunning() {return this->_running;}
private:
	uint8_t CheckMovement(uint8_t, uint8_t dist = 1);
	uint8_t PlaceFigure();
	uint8_t NewFigure();

	Glass _glass;
	Figure _figure, _nextFigure, _phantomFigure;

	uint32_t _points;

	uint16_t _velocity; // in millis
	std::chrono::time_point <std::chrono::system_clock> _lastTime; // in millis

	std::chrono::duration<double> _dTime;
	bool _running;
};

#endif // !PROGRAM_H