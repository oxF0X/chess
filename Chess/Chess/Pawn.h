#pragma once
#include "Pawn.h"
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn(std::string location, bool isWhite);
	virtual ~Pawn();
};