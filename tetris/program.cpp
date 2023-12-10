////////////////////////////////////////////////
//
//	Program tetris, program.cpp
//
//	Simple tetris in console
//
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////

#include "program.h"

// class Game

Game::Game() {
	this->_running = true;
	this->_velocity = 1000;
	this->_lastTime = std::chrono::system_clock::now();
	this->_dTime = std::chrono::duration <double> (0);
	this->_nextFigure.Generate();
}

Game::~Game() {

}

uint8_t Game::DoStep() {
	int keycode;

	_dTime = std::chrono::duration <double> {std::chrono::system_clock::now() - this->_lastTime};

	if (_kbhit()) {
		keycode = _getch();
		int gap = 0;
		std::cout << "keycode = " << keycode << "\n";

		switch (keycode)
		{
		case BD_GAME_KEYCODE__ESC:
			this->_running = false;
			break;

		case BD_GAME_KEYCODE__ENTER:
			break;

		case BD_GAME_KEYCODE__LEFT:
		case BD_GAME_KEYCODE__RIGHT:
		case BD_GAME_KEYCODE__DOWN:
		case BD_GAME_KEYCODE__UP:
			if (!this->CheckMovement(keycode, 1))
				this->_figure.Move(keycode);
			break;

		case BD_GAME_KEYCODE__SPACE:
			while (!this->CheckMovement(BD_GAME_KEYCODE__DOWN, gap + 1))
				gap++;

			if (this->_figure.IsActive())
				this->_figure.Move(BD_GAME_KEYCODE__DOWN, gap);

			this->PlaceFigure();
			this->NewFigure();
			break;

		case BD_GAME_KEYCODE__C:
			this->_glass.Reset();
			break;

		default:
			break;
		}
		this->Redraw();
	}
	else
		keycode = 0;

	if (this->_glass.Check())
		this->Redraw();

	if (_dTime > std::chrono::milliseconds(BD_GAME_TICK)) {
		if (this->_figure.IsActive()) {
			if (!this->CheckMovement(BD_GAME_KEYCODE__DOWN, 1))
				this->_figure.Move(BD_GAME_KEYCODE__DOWN, 1);
			else {
				this->PlaceFigure();
				this->NewFigure();
			}
		}
		else
			this->NewFigure();
		this->Redraw();
		this->_lastTime = std::chrono::system_clock::now();
	}

	return keycode;
}

uint8_t Game::Redraw() {
	system("cls");

	std::vector <std::vector <uint8_t>> cell = this->_glass.GetGlass();

	if (this->_figure.IsActive()) {
		for (int i = 0; i < 4; i++) {
			cell[this->_figure.GetCoordinates()[i].X][this->_figure.GetCoordinates()[i].Y] = 2;
		}
	}

	std::reverse(cell.begin(), cell.end());

 	for (auto i = cell.begin(); i != cell.end(); i++) {
		std::cout << "0 ";
		for (auto k = (*i).begin(); k != (*i).end(); k++) {
			switch (*k)
			{
			case 0:
				std::cout << "  ";
				break;
			case 1:
				std::cout << "##";
				break;
			case 2:
				std::cout << "$$";
				break;
			default:
				break;
			}
		}
		std::cout << " 0\n";
	}
	std::cout << "00";
	for (int i = 0; i < BD_GLASS__WIDTH; i++)
		std::cout << "00";
	std::cout << "00\n";



#ifdef DEBUG
	std::cout << "millis: " << _dTime << "\n";
	std::cout << "figX " << (int)this->_figure.GetPosition().first << " | figY " << (int)this->_figure.GetPosition().second << "\n";
#endif // DEBUG

	return 0;
}

uint8_t Game::CheckMovement(uint8_t dir, uint8_t dist) {
	this->_phantomFigure = this->_figure;
	this->_phantomFigure.Switch();
	this->_phantomFigure.Move(dir, dist);

	std::vector <Cell> cells = this->_phantomFigure.GetCoordinates();

	for (auto it = cells.begin(); it != cells.end(); it++) {
		if (it->X < 0 ||
			it->X > BD_GLASS__HEIGHT - 1 ||
			it->Y < 0 ||
			it->Y > BD_GLASS__WIDTH - 1)
			return 1;

		if (this->_glass.GetGlass()[it->X][it->Y] == 1)
			return 1;
	}

	return 0;
}

uint8_t Game::PlaceFigure() {
	if (this->_figure.IsActive()) {
		std::vector <Cell> cell = this->_figure.GetCoordinates();
		for (auto it = cell.begin(); it != cell.end(); it++)
			this->_glass.PutCell(it->X, it->Y);
		this->_figure.Switch();
	}
	return 0;
}

uint8_t Game::NewFigure() {
	this->_figure = this->_nextFigure;
	if (!this->_figure.IsActive()) this->_figure.Switch();;
	this->_nextFigure.Generate();
	return 0;
}