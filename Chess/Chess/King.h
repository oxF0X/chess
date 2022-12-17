#pragma once
#include "Figure.h"


class King : public Figure
{
public:
	King(std::string location, bool isWhite);
	virtual ~King();
	int isValidMove(const std::string& move) override;
	bool canEat(const std::string& move) override;
};