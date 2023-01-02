#pragma once

#include <iostream>
#include <string>
#include <math.h>

#define A_ASCII_CODE 97
#define ONE_ASCII_CODE 49
#define ZERO_ASCII_CODE 48
#define ROW 0
#define COL 1


class MathUtils
{
public:
	static std::string intLocationToStr(int col, int row);
	static int* strLocationToInt(std::string location);
};