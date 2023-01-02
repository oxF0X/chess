#include "Rook.h"
#include "Board.h"

Rook::Rook(const int& row, const int& col, bool isWhite,Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	this->_isFirstMove = true;
	this->_type = ROOK;
}

Rook::~Rook()
{
	return;
}

int Rook::isValidMove(const int& row, const int& col)
{
	int i, lower, bigger;
	if (row == this->_row)
	{
		lower = this->_col < col ? this->_col : col;
		bigger = lower + abs(this->_col - col);
		for (i = lower + 1; i < bigger; i++)
		{
			if (!this->_boardPtr->isEmpty(row, i))
			{
				return ILLEGAL_MOVE;
			}
		}
		this->_isFirstMove = false;
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
		
	}
	else if (col == this->_col)
	{
		lower = this->_row < row ? this->_row : row;
		bigger = lower + abs(this->_row - row);
		for (i = lower + 1; i < bigger; i++)
		{
			if (!this->_boardPtr->isEmpty(i, col))
			{
				return ILLEGAL_MOVE;
			}
		}
		this->_isFirstMove = false;
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
	}
	else
	{
		return ILLEGAL_MOVE;
	}
	
}
