////////////////////////////////////////////////
//
//	Program calculator, program.h
//
//	Reads expression as string, parces it, turns in postfix notation and counts result
//
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////

#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <conio.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

#define BDCALC_EC_OK 0
#define BDCALC_EC_HELP 1
#define BDCALC_EC_UNBALANCEDBRACKETS 2
#define BDCALC_EC_UNKNOWNIDENTIFIER 3
#define BDCALC_EC_INVALIDEXPRESSION 4
#define BDCALC_EC_EMPTYSTRING 5
#define BDCALC_EC_DIVBYZERO 13
#define BDCALC_EC_DEBUG_CANTOPENFILE 101
#define BDCALC_EC_DEBUG_WRONGDATE 102
#define BDCALC_EC_EXIT 255


#define BDCALC_DEBUG


const std::map <uint8_t, std::string> ErrorDictionary{
	{BDCALC_EC_DIVBYZERO, "division by zero"},
	{BDCALC_EC_HELP, "help"},
	{BDCALC_EC_UNBALANCEDBRACKETS, "unbalanced brackets"},
	{BDCALC_EC_UNKNOWNIDENTIFIER, "unknown keyword or identifier"},
	{BDCALC_EC_INVALIDEXPRESSION, "invalid expression"},
	{BDCALC_EC_EMPTYSTRING, "input string is empty"},
	{BDCALC_EC_DEBUG_CANTOPENFILE, "debugger can't open log file"},
	{BDCALC_EC_DEBUG_WRONGDATE, "debugger has wrong date"}
};

const std::map <char, uint8_t> SignDictionary{
	{',', 1},
	{'.', 1},
	{')', 1},
	{'(', 1},
	{'+', 2},
	{'-', 2},
	{'*', 3},
	{'/', 3},
	{'^', 4}
};

const std::map <std::string, uint8_t> KeywordDictionary{
	{"exit", 255},
	{"quit", 255},
	{"help", 1},
	{"?", 1}
};

struct Token {
	double _num = 0;
	char _sig = ' ';
	bool isInt = true;
};

class Debugger {
public:
	Debugger();
	~Debugger();

	uint8_t Log(std::string, uint8_t errcode);
private:
	uint8_t RefreshDate();

	std::fstream _logfile;
};

class Program {
public:
	Program();
	~Program();

	uint8_t Input();
	uint8_t Calculate();
private:
	uint8_t Reset();
	uint8_t ToPostfix();

	uint8_t Output(std::string str = "", uint8_t errcode = BDCALC_EC_OK);

	std::vector <Token> _token;
	double _result;

	Debugger* debugger;
};

#endif // !PROGRAM_H
