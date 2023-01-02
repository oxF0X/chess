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
	std::string map;
	if (col - this->_col == 2 && this->_row == row && this->_isFirstMove && !this->_boardPtr->isEmpty(this->_row, 7) && 
		this->_boardPtr->_figuresArr[this->_row][7]->getType() == ROOK && dynamic_cast<Rook*>(this->_boardPtr->_figuresArr[this->_row][7])->_isFirstMove && 
		this->_boardPtr->_figuresArr[this->_row][7]->getColor() == this->_color)
	{
		for (i = 4; i < SIZE; i++) // cheking if king not ins hah while mooving
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
		this->_boardPtr->_castlingDstCol = 4;
		this->_boardPtr->_castlingDstRow = this->_row;
		this->_boardPtr->_whiteOrBlack = !this->_boardPtr->_whiteOrBlack; // give the next move to the same team
		r = dynamic_cast<Rook*>(this->_boardPtr->_figuresArr[this->_row][7]);
		r->_isFirstMove = false;
		this->_isFirstMove = false;
		this->setLocation(5, this->_row);
		return VALID_MOVE;
	}

	if (this->_col - col == 2 && this->_row == row && this->_isFirstMove && !this->_boardPtr->isEmpty(this->_row, 0) &&
		this->_boardPtr->_figuresArr[this->_row][0]->getType() == ROOK && dynamic_cast<Rook*>(this->_boardPtr->_figuresArr[this->_row][0])->_isFirstMove &&
		this->_boardPtr->_figuresArr[this->_row][0]->getColor() == this->_color)
	{
		for (i = 3; i >= 2; i--) // cheking if king not ins hah while mooving
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
		this->_boardPtr->_castlingDstCol = 2;
		this->_boardPtr->_castlingDstRow = this->_row;
		this->_boardPtr->_whiteOrBlack = !this->_boardPtr->_whiteOrBlack;
		r = dynamic_cast<Rook*>(this->_boardPtr->_figuresArr[this->_row][0]);
		r->_isFirstMove = false;
		this->setLocation(this->_row, 1);
		this->_isFirstMove = false;
		return VALID_MOVE;
	}
	if ((abs(this->_row - row) == 1 && abs(this->_col - col) == 1 || // regular move
		abs(this->_row - row) == 0 && abs(this->_col - col) == 1 ||
		abs(this->_row - row) == 1 && abs(this->_col - col) == 0) &&		
		!(row >= SIZE || col >= SIZE || col < 0 || row < 0))
	{
		this->_isFirstMove = false; // nt the first move naymore
		this->setLocation(row, col);
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}

// This function changes king's location and board's king location
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