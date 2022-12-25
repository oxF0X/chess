#pragma once

#include "Figure.h"

class Board;

class Kinght : public Figure
{
public:
	Kinght(std::string location, bool isWhite, const Board* boardPtr);
	virtual ~Kinght();
	int isValidMove(const std::string& move) override;
};