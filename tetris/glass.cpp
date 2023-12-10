////////////////////////////////////////////////
//
//	Program tetris, glass.cpp
//
//	Simple tetris in console
// 
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////

#include "glass.h"

// class Glass

Glass::Glass() {
	this->Reset();
}

Glass::~Glass() {

}

uint8_t Glass::Reset() {
	for (auto i = _cell.begin(); i != _cell.end(); i++)
		for (auto k = (*i).begin(); k != (*i).end(); k++)
			*k = false;
	return 0;
}

uint8_t Glass::Randomize() {
	for (auto i = this->_cell.begin(); i != this->_cell.end(); i++)
		for (auto k = (*i).begin(); k != (*i).end(); k++) {
			*k = rand() % 3;
		}
	return 0;
}

uint8_t Glass::Check() {
	bool checked = false;
	for (auto i = this->_cell.begin(); i != this->_cell.end(); i++) {
		bool fullString = true;

		for (auto k = (*i).begin(); k != (*i).end(); k++)
			if (*k == false) {
				fullString = false;
				break;
			}

		if (fullString) {
			for (auto n = i; n != this->_cell.end() - 1; n++) {
				*n = *(n + 1);
			}
			*(this->_cell.end() - 1) = std::vector <uint8_t>(BD_GLASS__WIDTH, 0);
			checked = true;
		}
	}
	return checked;
}