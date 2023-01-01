#include "King.h"
#include <thread>
#include "Board.h"
#include <chrono>



King::King(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	this->_isFirstMove = true;
	this->_type = KING;
}

King::~King()
{
	return;
}

int King::isValidMove(const int& row, const int& col)
{
	Rook* r;
	int i, tmpCol, tmpRow;
	char msgToGraphics[1024];
	std::string map;
	r = dynamic_cast<Rook*>(this->_boardPtr->_figuresArr[this->_row][7]);
	if (col - this->_col == 2&& this->_row == row && this->_isFirstMove && !this->_boardPtr->isEmpty(this->_row, 7) && 
		this->_boardPtr->_figuresArr[this->_row][7]->getType() == ROOK && this->_boardPtr->_figuresArr[this->_row][7]->getColor() == this->_color)
	{
		for (i = 5; i < SIZE; i++)
		{
			this->_col++;
			if (this->_boardPtr->isEmpty(this->_row, i))
			{
				continue;
			}
			tmpRow = this->_boardPtr->_figuresArr[this->_row][i]->getRow();
			tmpCol = this->_boardPtr->_figuresArr[this->_row][i]->getCol();
			
			if (this->_boardPtr->isShah(this->_color, this->_row, i))
			{

				this->_boardPtr->_figuresArr[this->_row][i]->setLocation(tmpRow, tmpCol);

				return ILLEGAL_MOVE;
			}
		}

		this->_boardPtr->_isCastling = true;
		this->_boardPtr->_castlingSrcCol = 7;
		this->_boardPtr->_castlingSrcRow = this->_row;
		this->_boardPtr->_castlingDstCol = 5;
		this->_boardPtr->_castlingDstRow = this->_row;
		this->_boardPtr->_whiteOrBlack = !this->_boardPtr->_whiteOrBlack;
		r->_isFirstMove = false;
		this->_col = 6;
		this->_isFirstMove = false;
		if (this->_color == WHITE)
		{
			this->_boardPtr->_whiteKingRow = row;
			this->_boardPtr->_whiteKingCol = col;
			return VALID_MOVE;
		}
		this->_boardPtr->_blackKingRow = row;
		this->_boardPtr->_blackKingCol = col;
		return VALID_MOVE;
	}

	if (this->_col - col== 2 && this->_row == row && this->_isFirstMove && !this->_boardPtr->isEmpty(this->_row, 0) &&
		this->_boardPtr->_figuresArr[this->_row][0]->getType() == ROOK && this->_boardPtr->_figuresArr[this->_row][0]->getColor() == this->_color)
	{
		for (i = 4; i >= 2; i--)
		{
			this->_col++;
			if (this->_boardPtr->isEmpty(this->_row, i))
			{
				continue;
			}
			tmpRow = this->_boardPtr->_figuresArr[this->_row][i]->getRow();
			tmpCol = this->_boardPtr->_figuresArr[this->_row][i]->getCol();
			if (this->_boardPtr->isShah(this->_color, this->_row, i))
			{
				this->_boardPtr->_figuresArr[this->_row][i]->setLocation(tmpRow, tmpCol);
			}
		}

		this->_boardPtr->_isCastling = true;
		this->_boardPtr->_castlingSrcCol = 0;
		this->_boardPtr->_castlingSrcRow = this->_row;
		this->_boardPtr->_castlingDstCol = 3;
		this->_boardPtr->_castlingDstRow = this->_row;
		this->_boardPtr->_whiteOrBlack = !this->_boardPtr->_whiteOrBlack;
		r->_isFirstMove = false;
		this->_col = 2;
		this->_isFirstMove = false;
		if (this->_color == WHITE)
		{
			this->_boardPtr->_whiteKingRow = row;
			this->_boardPtr->_whiteKingCol = col;
			return VALID_MOVE;
		}
		this->_boardPtr->_blackKingRow = row;
		this->_boardPtr->_blackKingCol = col;
		return VALID_MOVE;
	}
	if (abs(this->_row - row) == 1 && abs(this->_col - col) == 1 ||
		abs(this->_row - row) == 0 && abs(this->_col - col) == 1 ||
		abs(this->_row - row) == 1 && abs(this->_col - col) == 0)
	{
		this->_row = row;
		this->_col = col;
		this->_isFirstMove = false;
		if (this->_color == WHITE)
		{
			this->_boardPtr->_whiteKingRow = row;
			this->_boardPtr->_whiteKingCol = col;
			return VALID_MOVE;
		}
		this->_boardPtr->_blackKingRow = row;
		this->_boardPtr->_blackKingCol = col;
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}


void King::setLocation(const int& row, const int& col)
{
	this->_row = row;
	this->_col = col;
	if (this->_color == WHITE)
	{
		this->_boardPtr->_whiteKingRow = row;
		this->_boardPtr->_whiteKingCol = col;
		return;
	}
	this->_boardPtr->_blackKingRow = row;
	this->_boardPtr->_blackKingCol = col;
}