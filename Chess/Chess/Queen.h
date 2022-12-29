#pragma once

#include "Rook.h"
#include "Bishop.h"


class Board;

class Queen : public Rook, public Bishop
{
public:
	Queen(const int& row, const int& col, bool isWhite, Board* boardPtr);
	virtual ~Queen();
	int isValidMove(const int& row, const int& col) override;
};
