#include "Knight.h"

Kinght::Kinght(const int& row, const int& col, bool isWhite, const Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

Kinght::~Kinght()
{
	return;
}

int Kinght::isValidMove(const int& row, const int& col)
{
	return 0;
}
