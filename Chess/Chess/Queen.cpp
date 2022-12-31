#include "Queen.h"
#include "Board.h"

Queen::Queen(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr), Rook(row, col, isWhite, boardPtr), Bishop(row, col, isWhite, boardPtr)
{
	this->_type = QUEEN;
}

Queen::~Queen()
{
	return;
}

int Queen::isValidMove(const int& row, const int& col)
{
	if (Rook::isValidMove(row, col) == VALID_MOVE|| Bishop::isValidMove(row, col) == VALID_MOVE)
	{
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}
