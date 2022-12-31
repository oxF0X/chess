#pragma once
#include "Figure.h"

class Board;

class Pawn : public Figure
{
public:
	Pawn(const int& row, const int& col, bool isWhite, Board* boardPtr);
	virtual ~Pawn();
	int isValidMove(const int& row, const int& col) override;
	Figure* getNewFigure() const;

private:
	Figure* _newFigure;
	bool _isFirstMove;
};