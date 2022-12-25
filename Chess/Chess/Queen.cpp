#include "Queen.h"


Queen::Queen(std::string location, bool isWhite, const Board* boardPtr) : Figure(location, isWhite, boardPtr), Rook(location, isWhite, boardPtr), Bishop(location, isWhite, boardPtr)
{
	return;
}

Queen::~Queen()
{
	return;
}

int Queen::isValidMove(const std::string& move)
{
	return 0;
}
