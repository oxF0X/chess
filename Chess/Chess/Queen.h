#pragma once

#include "Rook.h"
#include "Bishop.h"

class Queen : public Rook, public Bishop
{
public:
	Queen(std::string location, bool isWhite);
	virtual ~Queen();
	int isValidMove(const std::string& move) override;
	bool canEat(const std::string& move) override;
};
