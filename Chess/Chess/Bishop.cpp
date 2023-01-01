#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	this->_type = BISHOP;
}

Bishop::~Bishop()
{
	return;
}

int Bishop::isValidMove(const int& row, const int& col)
{
	int i, j, lowerRow, biggerRow, lowerCol, biggerCol, tmpCol;
	if (abs(this->_row - row) == abs(this->_col - col))
	{
		if (this->_col < col && this->_row < row)
		{
			for (j = this->_col + 1, i = this->_row + 1; i < row; i++, j++)
			{
				if (!this->_boardPtr->isEmpty(i, j))
				{
					return ILLEGAL_MOVE;
				}
			}
		}
		else if (this->_col > col && this->_row < row)
		{
			for (j = this->_col - 1, i = this->_row +1; i < row; i++, j--)
			{
				if (!this->_boardPtr->isEmpty(i, j))
				{
					return ILLEGAL_MOVE;
				}
			}
		}
		else if (this->_row > row && this->_col < col)
		{
			for (j = this->_col + 1, i = this->_row - 1; i < row; i--, j++)
			{
				if (!this->_boardPtr->isEmpty(i, j))
				{
					return ILLEGAL_MOVE;
				}
			}
		}
		else
		{
			for (j = this->_col - 1, i = this->_row - 1; i < row; i--, j--)
			{
				if (!this->_boardPtr->isEmpty(i, j))
				{
					return ILLEGAL_MOVE;
				}
			}
		}
		/*lowerRow = this->_row < row ? this->_row : row;
		biggerRow = lowerRow + abs(this->_row - row);
		lowerCol = this->_col < col ? this->_col : col;
		biggerCol = lowerCol + abs(this->_col - col);
		if (this->_row < row)
		{
			tmpCol = this->_col;
		}
		else
		{
			tmpCol = col;
		}
		if (tmpCol <= col)
		{
			for (i = lowerRow + 1, j = tmpCol + 1; i < biggerRow; i++, j++)
			{
				if (!this->_boardPtr->isEmpty(i, j))
				{
					return ILLEGAL_MOVE;
				}
			}
		}
		else
		{
			for (i = lowerRow + 1, j = tmpCol - 1; i < biggerRow; i++, j--)
			{
				if (!this->_boardPtr->isEmpty(i, j))
				{
					return ILLEGAL_MOVE;
				}
			}
		}
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;*/
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}



