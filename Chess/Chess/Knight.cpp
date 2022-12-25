#include "Knight.h"

Kinght::Kinght(std::string location, bool isWhite, const Board* boardPtr) : Figure(location, isWhite, boardPtr)
{
	return;
}

Kinght::~Kinght()
{
	return;
}

int Kinght::isValidMove(const std::string& move)
{
	return 0;
}
