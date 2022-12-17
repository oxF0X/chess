#include "Queen.h"


Queen::Queen(std::string location, bool isWhite) : Figure(location, isWhite), Rook(location, isWhite), Bishop(location, isWhite)
{
	return;
}

Queen::~Queen()
{
	return;
}
