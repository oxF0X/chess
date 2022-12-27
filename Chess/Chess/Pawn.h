#pragma once
#include "Figure.h"

class Board;

class Pawn : public Figure
{
public:
	Pawn(const int& row, const int& col, bool isWhite, const Board* boardPtr);
	virtual ~Pawn();
	int isValidMove(const int& row, const int& col) override;
};