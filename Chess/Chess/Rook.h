#pragma once

#include "Figure.h"
#include "MathUtils.h"

class Board;

class Rook : virtual public Figure
{
public:
	Rook(const int& row, const int& col, bool isWhite, Board* boardPtr);
	virtual ~Rook();
	int isValidMove(const int& row, const int& col) override;
};