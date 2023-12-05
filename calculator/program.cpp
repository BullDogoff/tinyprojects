////////////////////////////////////////////////
//
//	Program calculator, program.cpp
//
//	Reads expression as string, parces it, turns in postfix notation and counts result
//
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////

#include "program.h"

Debugger::Debugger() {
	RefreshDate();
}

Debugger::~Debugger() {}

uint8_t Debugger::Log(std::string str, uint8_t errcode) {
	RefreshDate();
	_logfile << std::chrono::floor <std::chrono::seconds>(std::chrono::system_clock::now()) << " --- " << str;

	return BDCALC_EC_OK;
}

uint8_t Debugger::RefreshDate() {
	if (_logfile.is_open()) return BDCALC_EC_OK;

	std::stringstream ss;
	std::string _filename;
	ss << ".\\" << std::chrono::floor <std::chrono::days>(std::chrono::system_clock::now()) << ".log";
	ss >> _filename;
	_logfile.open(_filename, std::ios_base::app);

	return BDCALC_EC_OK;
}


Program::Program() {
	Reset();

	debugger = new Debugger();
}

Program::~Program() {
	delete debugger;
}

uint8_t Program::Input() {
	std::string str;
	char previousSymbol = ' ';
	_token.clear();
	int decimalDigits = 0;

	Output("Enter expression: ");
	getline(std::cin, str);

#ifdef BDCALC_DEBUG
	debugger->Log("Enter expression: " + str + "\n", BDCALC_EC_OK);
#endif // BDCALC_DEBUG

	for (auto it = KeywordDictionary.begin(); it != KeywordDictionary.end(); it++) {
		if (str.find(it->first) != std::string::npos)
			switch (it->second) {
			case BDCALC_EC_EXIT:
				Output("", BDCALC_EC_EXIT);
				return BDCALC_EC_EXIT;
				break;
			case BDCALC_EC_HELP:
				Output("", BDCALC_EC_HELP);
				return BDCALC_EC_HELP;
				break;
			default:
				break;
			}
	}

	if (str.begin() == str.end()) {
		this->Reset();
		return BDCALC_EC_EMPTYSTRING;
	}

	for (auto it = str.begin(); it != str.end();) {
		if (!isdigit(*it) && SignDictionary.find(*it) == SignDictionary.end()) str.erase(it);
		else it++;
	}

	for (auto it = str.begin(); it != str.end(); it++) {
		if ((*it == '.' || *it == ',') && (it == str.begin() || !isdigit(*(it - 1))))
			str.insert(it, '0');
	}

	if (str.empty()) {
		Output("empty string", BDCALC_EC_UNKNOWNIDENTIFIER);
		this->Reset();
		return BDCALC_EC_UNKNOWNIDENTIFIER;
	}

	for (auto it = str.begin(); it != str.end(); it++) {
		if (isdigit(*it)) {
			if (!isdigit(previousSymbol)) {
				_token.push_back(Token());
				_token.back().isInt = true;
			}

			if (isdigit(previousSymbol) && !decimalDigits)
				_token.back()._num *= 10;

			_token.back()._num += (*it -48) / pow(10, decimalDigits);

			if (decimalDigits)
				decimalDigits++;
		}
		else if (*it == '.' || *it == ',') {
			if (decimalDigits) {
				Output("too many dots", BDCALC_EC_INVALIDEXPRESSION);
				this->Reset();
				return BDCALC_EC_INVALIDEXPRESSION;
			}
			decimalDigits = 1;
			str.erase(it);
			it--;
		}
		else {
			decimalDigits = 0;
			_token.push_back(Token());
			_token.back().isInt = false;

			if (SignDictionary.find(*it) != SignDictionary.end()) {
				if (*it == '(' && isdigit(previousSymbol)) { // a(b+c) => a*(b+c)
					_token.back()._sig = '*';
					_token.push_back(Token());
					_token.back().isInt = false;
				}
				_token.back()._sig = *it;
			}
		}
		previousSymbol = *it;
	}

	int8_t brCount = 0;
	int8_t operandCount = -1;

	for (auto it = _token.begin(); it != _token.end(); it++) {
		if (!it->isInt && it->_sig == '(') brCount += 1;
		if (!it->isInt && it->_sig == ')') brCount -= 1;

		if (it->isInt) operandCount += 1;
		else if (SignDictionary.find(it->_sig)->second > 1) operandCount -=1;
	}

	if (brCount) {
		Output("", BDCALC_EC_UNBALANCEDBRACKETS);
		this->Reset();
		return BDCALC_EC_UNBALANCEDBRACKETS;
	}

	if (operandCount && _token.size() > 1) {
		Output("operand count", BDCALC_EC_INVALIDEXPRESSION);
		this->Reset();
		return BDCALC_EC_INVALIDEXPRESSION;
	}

	return BDCALC_EC_OK;
}

uint8_t Program::Calculate() {
	if (uint8_t errcode = ToPostfix()) {
		Output("", errcode);
		return errcode;
	}

	double opA = 0, opB = 0;
	std::vector <double> stack;

	for (int i = 0; i < _token.size(); i++) {
		if (_token[i].isInt)
			stack.push_back(_token[i]._num);
		else {
			opB = stack.back();
			stack.pop_back();
			opA = stack.back();
			stack.pop_back();

			switch (_token[i]._sig)
			{
			case '+':
				stack.push_back(opA + opB);
				break;
			case '-':
				stack.push_back(opA - opB);
				break;
			case '*':
				stack.push_back(opA * opB);
				break;
			case '/':
				if (opB == 0) {
					Output("", BDCALC_EC_DIVBYZERO);
					return BDCALC_EC_DIVBYZERO;
				}
				stack.push_back(opA / opB);
				break;
			case '^':
				stack.push_back(pow(opA, opB));
				break;
			default:
				break;
			}
		}
	}

	_result = stack.back();

	Output(std::string("Result: " + std::to_string(_result)) + "\n\n");

#ifdef BDCALC_DEBUG
	debugger->Log("Result: " + std::to_string(_result) + "\n", BDCALC_EC_OK);
#endif // BDCALC_DEBUG

	return BDCALC_EC_OK;
}

uint8_t Program::Reset() {
	_token.clear();
	_result = 0;

	return BDCALC_EC_OK;
}

uint8_t Program::ToPostfix() {
	std::vector <Token> stack;
	std::vector <Token> fin;

	fin.clear();

	for (int i = 0; i < _token.size(); i++)
	{
		if (_token[i].isInt) //если операнд
			fin.push_back(_token[i]); //переносим в итоговую строку

		else if (stack.empty() || _token[i]._sig == '(') //если стек пустой или попалась открывающая скобка
			stack.push_back(_token[i]); //бросаем в стек
		else if (_token[i]._sig == ')') { // если попалась закрывающая скобка
			while (stack.back()._sig != '(') { //до открывающей скобки в стеке
				fin.push_back(stack.back()); //переносим в итоговую строку очередной элемент
				stack.pop_back(); //удаляем его из стека
			}
			stack.pop_back(); //удаляем открывающую скобку из стека
		}
		else if (SignDictionary.find(_token[i]._sig)->second > SignDictionary.find(stack.back()._sig)->second) //если приоритет оператора больше, чем у верхнего в стеке
			stack.push_back(_token[i]); //бросаем его в стек
		else {
			while (SignDictionary.find(_token[i]._sig)->second <= SignDictionary.find(stack.back()._sig)->second) { //пока приоритет оператора меньше либо равен верхнему в стеке
				fin.push_back(stack.back()); //переносим оператор из стека в итоговую строку
				stack.pop_back(); //удаляем его из стека
				if (stack.empty()) break; //если стек пустой - выходим из цикла
			}
			stack.push_back(_token[i]); //бросаем оператор в стек
		}
	}

	while (stack.size() != 0) {
		fin.push_back(stack.back());
		stack.pop_back();
	}

	_token = fin;

	return 0;
}

uint8_t Program::Output(std::string str, uint8_t errcode) {
	switch (errcode)
	{
	case BDCALC_EC_OK:
		std::cout << str;
		break;
	case BDCALC_EC_HELP:
		std::cout << "List of all keywords:\n";
		for (auto it = KeywordDictionary.begin(); it != KeywordDictionary.end(); it++) {
			std::cout << "	" << it->first << "\n";
		}
		std::cout << "\n";
		break;
	case BDCALC_EC_EXIT:
		std::cout << "\n\nCalculator v. 1.1b by BullDogoff, (c) 2023\n\n";
		debugger->Log("Calculator v. 1.1b by BullDogoff, (c) 2023\n\n", BDCALC_EC_OK);
		break;
	default:
		std::cout << "!ERROR: " << ErrorDictionary.find(errcode)->second << " " << str << "\n\n";
		break;
	}

	return BDCALC_EC_OK;
}
