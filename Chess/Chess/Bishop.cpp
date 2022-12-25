#include "Bishop.h"

Bishop::Bishop(std::string location, bool isWhite, const Board* boardPtr) : Figure(location, isWhite, boardPtr)
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



