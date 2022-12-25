#include "Pawn.h"

Pawn::Pawn(std::string location, bool isWhite, const Board* boardPtr) : Figure(location, isWhite, boardPtr)
{
	return;
}

Pawn::~Pawn()
{
	return;
}

int Pawn::isValidMove(const std::string& move)
{
	return 0;
}
