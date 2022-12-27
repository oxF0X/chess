#include "Rook.h"
#include "Board.h"

Rook::Rook(const int& row, const int& col, bool isWhite, const Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

Rook::~Rook()
{
	return;
}

int Rook::isValidMove(const int& row, const int& col)
{
	if (col == this->_col)
	{
		for (int i = abs(col - this->_col); i > 0; i--)
		{
			if (!this->_boardPtr->isEmpty(i, row))
			{
				return ILLEGAL_MOVE;
			}
		}
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
		
	}
	else if (row == this->_row)
	{
		for (int i = abs(row - this->_row); i > 0; i--)
		{
			if (!this->_boardPtr->isEmpty(col, i))
			{
				return ILLEGAL_MOVE;
			}
		}
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
	}
	else
	{
		return ILLEGAL_MOVE;
	}
	
}
