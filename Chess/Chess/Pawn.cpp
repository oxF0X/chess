#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

Pawn::~Pawn()
{
	return;
}

int Pawn::isValidMove(const int& row, const int& col)
{
	bool valid1 = (abs(this->_row - row) == 1 && abs(this->_col - col)) && !this->_boardPtr->isEmpty(row, col) == 0;
	bool valid2 = (abs(this->_row - row) == 0 && abs(this->_col - col)) && !this->_boardPtr->isEmpty(row, col) == 1;
	bool valid3 = (abs(this->_row - row) == 1 && abs(this->_col - col) == 1) && this->_boardPtr->isEmpty(row, col);
	bool valid4 = (abs(this->_row - row) == 1 && abs(this->_col - col) == 1) && this->_boardPtr->isEmpty(row, col);

	if (valid1 || valid2 || valid3 || valid4)
	{
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}
