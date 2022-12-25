#pragma once
#include "Figure.h"


class Board;


class Bishop : virtual public Figure
{
public:
	Bishop(std::string location, bool isWhite, const Board* boardPtr);
	virtual ~Bishop();
	int isValidMove(const std::string& move) override;
};