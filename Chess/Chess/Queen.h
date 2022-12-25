#pragma once

#include "Rook.h"
#include "Bishop.h"


class Board;

class Queen : public Rook, public Bishop
{
public:
	Queen(std::string location, bool isWhite, const Board* boardPtr);
	virtual ~Queen();
	int isValidMove(const std::string& move) override;
};
