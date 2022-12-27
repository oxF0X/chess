#include "King.h"

King::King(const int& row, const int& col, bool isWhite, const Board* boardPtr): Figure(row, col, isWhite, boardPtr)
{
	return;
}

King::~King()
{
	return;
}

int King::isValidMove(const int& row, const int& col)
{
	return 0;
}
