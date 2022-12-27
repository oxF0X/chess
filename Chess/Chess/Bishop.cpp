#include "Bishop.h"

Bishop::Bishop(const int& row, const int& col, bool isWhite, const Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

Bishop::~Bishop()
{
	return;
}

int Bishop::isValidMove(const int& row, const int& col)
{
	return 0;
}



