#include "King.h"
#include "Board.h"


King::King(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

King::~King()
{
	return;
}

int King::isValidMove(const int& row, const int& col)
{
	if (abs(this->_row - row) == 1 && abs(this->_col - col) == 1 ||
		abs(this->_row - row) == 0 && abs(this->_col - col) == 1 ||
		abs(this->_row - row) == 1 && abs(this->_col - col) == 0)
	{
		this->_row = row;
		this->_col = col;
		if (this->_color == WHITE)
		{
			this->_boardPtr->_whiteKingRow = row;
			this->_boardPtr->_whiteKingCol = col;
			return VALID_MOVE;
		}
		this->_boardPtr->_blackKingRow = row;
		this->_boardPtr->_blackKingCol = col;
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}
