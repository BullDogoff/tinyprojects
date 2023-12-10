////////////////////////////////////////////////
//
//	Program tetris, main.h
//
//	Simple tetris in console
// 
//	(c) BullDogoff, 2023
//
////////////////////////////////////////////////
#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define BD_GAME_TICK 1000 // in millis

#define BD_GAME_KEYCODE__ESC 27
#define BD_GAME_KEYCODE__R 114
#define BD_GAME_KEYCODE__C 99
#define BD_GAME_KEYCODE__G 103
#define BD_GAME_KEYCODE__ENTER 13
#define BD_GAME_KEYCODE__UP 72
#define BD_GAME_KEYCODE__LEFT 75
#define BD_GAME_KEYCODE__RIGHT 77
#define BD_GAME_KEYCODE__DOWN 80

#define BD_GLASS__WIDTH 10
#define BD_GLASS__HEIGHT 20

#endif // !MAIN_H