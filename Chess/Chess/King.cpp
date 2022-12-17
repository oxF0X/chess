#include "King.h"

King::King(std::string location, bool isWhite): Figure(location, isWhite)
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

bool King::canEat(const std::string& move)
{
	return false;
}
