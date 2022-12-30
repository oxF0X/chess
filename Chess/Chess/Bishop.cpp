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
	int i, j;
	if (abs(this->_row - row) == abs(this->_col - col))
	{
		i = this->_row < row ? this->_row : row;
		j = this->_col < col ? this->_col : col;
		for (i = this->_row + 1, j = this->_col + 1; i < abs(this->_row - row); i++, j++)
		{
			if (!this->_boardPtr->isEmpty(i, j))
			{
				return ILLEGAL_MOVE;
			}
		}
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}



