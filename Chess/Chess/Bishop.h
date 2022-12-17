#pragma once
#include "Figure.h"

class Bishop : public Figure
{
public:
	Bishop(std::string location, bool isWhite);
	virtual ~Bishop();
	int isValidMove(const std::string& move) override;
	bool canEat(const std::string& move) override;
};