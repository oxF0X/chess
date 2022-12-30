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
	bool valid1 = (this->_row - row) == -1 && this->_col - col == 0 && !this->_boardPtr->isEmpty(row, col) == 0 && this->getColor() == WHITE;
	bool valid2 = (this->_row - row) == -1 && abs(this->_col - col) == 1 && !this->_boardPtr->isEmpty(row, col) == 1 && this->getColor() == WHITE;
	bool valid3 = (this->_row - row) == 1 && this->_col - col == 0 && !this->_boardPtr->isEmpty(row, col) == 0 && this->getColor() == BLACK;
	bool valid4 = (this->_row - row) == 1 && abs(this->_col - col) == 1 && !this->_boardPtr->isEmpty(row, col) == 1 && this->getColor() == BLACK;


	if (valid1 || valid2 || valid3 || valid4)
	{
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}
