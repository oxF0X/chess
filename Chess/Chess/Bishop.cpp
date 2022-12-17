#include "Bishop.h"

Bishop::Bishop(std::string location, bool isWhite) : Figure(location,isWhite)
{
	return;
}

Bishop::~Bishop()
{
	return;
}

int Bishop::isValidMove(const std::string& move)
{
	return 0;
}

bool Bishop::canEat(const std::string& move)
{
	return false;
}


