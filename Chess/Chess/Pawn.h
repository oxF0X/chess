#pragma once
#include "Pawn.h"
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn(std::string location, bool isWhite);
	virtual ~Pawn();
	int isValidMove(const std::string& move) override;
	bool canEat(const std::string& move) override;
};