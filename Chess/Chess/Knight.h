#pragma once
#include "Knight.h"
#include "Figure.h"

class Kinght : public Figure
{
public:
	Kinght(std::string location, bool isWhite);
	virtual ~Kinght();
	int isValidMove(const std::string& move) override;
	bool canEat(const std::string& move) override;
};