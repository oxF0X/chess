#include "Knight.h"
#include "Board.h"

Kinght::Kinght(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	this->_type = KNIGHT;
}

Kinght::~Kinght()
{
	return;
}

int Kinght::isValidMove(const int& row, const int& col)
{
	bool valid1 = abs(this->_row - row) == 1 && abs(this->_col - col) == 2;
	bool valid2 = abs(this->_row - row) == 2 && abs(this->_col - col) == 1;

	if (valid1 || valid2)
	{
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}
