////////////////////////////////////////////////
//
//	Program calculator, main.cpp
//
//	Reads expression as string, parces it, turns in postfix notation and counts result
//
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////

#include "program.h"

int main() {
	Program* program = new Program();

	system("cls");

	while (true) {
		switch (program->Input())
		{
		case BDCALC_EC_EXIT:
			std::cout <<"Press any key...";
			_getch();

			return 0;
			break;
		case BDCALC_EC_OK:
			program->Calculate();
			break;
		default:
			break;
		}
	}

	return 0;
}
