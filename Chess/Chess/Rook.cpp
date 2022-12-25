#include "Rook.h"
#include "Board.h"

Rook::Rook(std::string location, bool isWhite, const Board* boardPtr) : Figure(location, isWhite, boardPtr)
{
	return;
}

Rook::~Rook()
{
	return;
}

int Rook::isValidMove(const std::string& move)
{
	int* dstLocation = MathUtils::strLocationToInt(move);
	int* srcLocation = MathUtils::strLocationToInt(this->_location);
	if (dstLocation[COL] == srcLocation[COL])
	{
		for (int i = abs(dstLocation[COL] - srcLocation[COL]); i > 0; i--)
		{
			if (!this->_boardPtr->isEmpty(dstLocation[i], dstLocation[ROW]))
			{
				return ILLEGAL_MOVE;
			}
		}
		return VALID_MOVE;
		
	}
	else if (dstLocation[ROW] == srcLocation[ROW])
	{
		for (int i = abs(dstLocation[ROW] - srcLocation[ROW]); i > 0; i--)
		{
			if (!this->_boardPtr->isEmpty(dstLocation[COL], dstLocation[i]))
			{
				return ILLEGAL_MOVE;
			}
		}
		return VALID_MOVE;
	}
	else
	{
		return ILLEGAL_MOVE;
	}
	
}
