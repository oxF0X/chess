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
	int i, j, lowerRow, biggerRow, lowerCol, biggerCol, difference;
	if (abs(this->_row - row) == abs(this->_col - col))
	{
		lowerRow = this->_row < row ? this->_row : row;
		biggerRow = lowerRow + abs(this->_row - row);
		lowerCol = this->_col < col ? this->_col : col;
		biggerCol = lowerCol + abs(this->_col - col);
		//difference = this->_col - col;
		difference =  this->_col - col;

		for (j = abs(difference) - 1, i = lowerRow + 1; j > 0; i++, j--)
		{
			difference + j > SIZE ? difference * -1 : difference;
			if (!this->_boardPtr->isEmpty(i, this->_col + j + difference))
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



