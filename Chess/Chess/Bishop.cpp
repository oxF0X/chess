#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

Bishop::~Bishop()
{
	return;
}

int Bishop::isValidMove(const int& row, const int& col)
{
	if (abs(this->_row - row) == abs(this->_col - col))
	{
		this->_row = row;
		this->_col = col;
		for (int i = this->_row, j = this->_col; i < row; i++, j++)
		{
			if (!this->_boardPtr->isEmpty(i, j))
			{
				return ILLEGAL_MOVE;
			}
		}
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}



