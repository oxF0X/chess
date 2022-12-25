#include "King.h"

King::King(std::string location, bool isWhite, const Board* boardPtr): Figure(location, isWhite, boardPtr)
{
	return;
}

King::~King()
{
	return;
}

int King::isValidMove(const std::string& move)
{
	return 0;
}
