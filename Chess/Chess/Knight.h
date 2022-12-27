#pragma once

#include "Figure.h"

class Board;

class Kinght : public Figure
{
public:
	Kinght(const int& row, const int& col, bool isWhite, const Board* boardPtr);
	virtual ~Kinght();
	int isValidMove(const int& row, const int& col) override;
};