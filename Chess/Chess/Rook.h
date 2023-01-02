#pragma once

#include "Figure.h"
#include "MathUtils.h"

class Board;

class Rook : virtual public Figure
{
	friend class King;
public:
	Rook(const int& row, const int& col, bool isWhite, Board* boardPtr);
	virtual ~Rook();
	int isValidMove(const int& row, const int& col) override;
	bool isFirstMove() const;
	void setFirstMove(bool move);

private:
	bool _isFirstMove;
};