#include "Pawn.h"

Pawn::Pawn(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	return;
}

Pawn::~Pawn()
{
	return;
}

int Pawn::isValidMove(const int& row, const int& col)
{
	return 0;
}
