#pragma once

#include "Figure.h"
#include "MathUtils.h"

class Board;

class Rook : virtual public Figure
{
public:
	Rook(std::string location, bool isWhite, const Board* boardPtr);
	virtual ~Rook();
	int isValidMove(const std::string& move) override;
};