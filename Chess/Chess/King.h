#pragma once
#include "Figure.h"

class Board;

class King : public Figure
{
public:
	King(const int& row, const int& col, bool isWhite, const Board *boardPtr);
	virtual ~King();
	int isValidMove(const int& row, const int& col) override;
};