#include "Rook.h"
#include "Board.h"

Rook::Rook(const int& row, const int& col, bool isWhite,Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

Rook::~Rook()
{
	return;
}

int Rook::isValidMove(const int& row, const int& col)
{
	int i;
	if (row == this->_row)
	{
		i = this->_col < col ? this->_col : col;
		for (i += 1; i < abs(i - col); i++)
		{
			if (!this->_boardPtr->isEmpty(row, i))
			{
				return ILLEGAL_MOVE;
			}
		}
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
		
	}
	else if (col == this->_col)
	{
		i = this->_row < row ? this->_row : row;
		for (i += 1; i < abs(i - row); i++)
		{
			if (!this->_boardPtr->isEmpty(i, col))
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
