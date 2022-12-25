#pragma once
#include "Figure.h"

class Board;

class Pawn : public Figure
{
public:
	Pawn(std::string location, bool isWhite, const Board* boardPtr);
	virtual ~Pawn();
	int isValidMove(const std::string& move) override;
};