#pragma once
#include "Figure.h"
#include "Board.h"

class Board;

class King : public Figure
{
	friend class Rook;
public:
	King(const int& row, const int& col, bool isWhite, Board *boardPtr);
	virtual ~King();
	int isValidMove(const int& row, const int& col) override;
	void setLocation(const int& row, const int& col) override;
	bool isFirstMove() const;
	void setFirstMove(bool move);

private:
	bool _isFirstMove;
};