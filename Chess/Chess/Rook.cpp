#include "Rook.h"

Rook::Rook(std::string location, bool isWhite) : Figure(location, isWhite)
{
	return;
}

Rook::~Rook()
{
	return;
}

int Rook::isValidMove(const std::string& move)
{
	return 0;
}

bool Rook::canEat(const std::string& move)
{
	return false;
}
