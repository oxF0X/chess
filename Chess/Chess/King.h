#pragma once
#include "Figure.h"

class Board;

class King : public Figure
{
public:
	King(std::string location, bool isWhite, const Board *boardPtr);
	virtual ~King();
	int isValidMove(const std::string& move) override;
};