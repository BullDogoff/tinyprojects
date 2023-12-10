////////////////////////////////////////////////
//
//	Program tetris, figure.cpp
//
//	Simple tetris in console
// 
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////

#include "figure.h"
#include "glass.h"

// class Figure

Figure::Figure() {
	this->_positionX = BD_GLASS__HEIGHT - 4;
	this->_positionY = BD_GLASS__WIDTH / 2;

	for (int i = 0; i < 4; i++)
		_cell[i] = {0, 0};

	this->_active = false;
}

Figure::~Figure() {

}

uint8_t Figure::Generate() {
	uint8_t n = rand() % 5;
	for (int i = 0; i < 4; i++) {
		_cell[i] = figureDictionary.find(n)->second[i];
	}
	return 0;
}

std::vector <Cell> Figure::GetCoordinates() {
	std::vector <Cell> coordinates;
	for (int i = 0; i < 4; i++)
		coordinates.push_back(Cell(this->_positionX + this->_cell[i].X, this->_positionY + this->_cell[i].Y));

	return coordinates;
}

uint8_t Figure::MoveDown(uint8_t d) {
	this->_positionX -= d;
	return 0;
}

uint8_t Figure::MoveRight() {
	this->_positionY += 1;
	return 0;
}

uint8_t Figure::MoveLeft() {
	this->_positionY -= 1;
	return 0;
}

uint8_t Figure::Rotate() {
	Cell tempCell;
	for (int i = 0; i < 4; i++) {
		tempCell = this->_cell[i];
		this->_cell[i].X = -tempCell.Y;
		this->_cell[i].Y = tempCell.X;
	}
	return 0;
}

uint8_t Figure::Move(uint8_t dir, uint8_t dist) {
	switch (dir)
	{
	case BD_GAME_KEYCODE__LEFT:
		this->_positionY -=1;
		break;
	case BD_GAME_KEYCODE__RIGHT:
		this->_positionY += 1;
		break;
	case BD_GAME_KEYCODE__UP:
		this->Rotate();
		break;
	case BD_GAME_KEYCODE__DOWN:
		this->_positionX -= dist;
		break;
	default:
		break;
	}
	
	return 0;
}