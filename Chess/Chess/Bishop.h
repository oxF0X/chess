#pragma once
#include "Figure.h"


class Board;


class Bishop : virtual public Figure
{
public:
	Bishop(const int& row, const int& col, bool isWhite, const Board* boardPtr);
	virtual ~Bishop();
	int isValidMove(const int& row, const int& col) override;
};