#include "Queen.h"


Queen::Queen(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr), Rook(row, col, isWhite, boardPtr), Bishop(row, col, isWhite, boardPtr)
{
	return;
}

Queen::~Queen()
{
	return;
}

int Queen::isValidMove(const int& row, const int& col)
{
	return 0;
}
