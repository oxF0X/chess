#pragma once
#include "Rook.h"

class Rook : public Figure
{
public:
	Rook(std::string location, bool isWhite);
	virtual ~Rook();
	int isValidMove(const std::string& move) override;
	bool canEat(const std::string& move) override;
};