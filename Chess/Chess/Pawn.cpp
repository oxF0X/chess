#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(const int& row, const int& col, bool isWhite, Board* boardPtr) : Figure(row, col, isWhite, boardPtr)
{
	this->_isFirstMove = true;
	this->_firstMove2Rows = false;
	this->_type = PAWN;
	this->_newFigure = nullptr;
}

Pawn::~Pawn()
{
	return;
}

int Pawn::isValidMove(const int& row, const int& col)
{
	Queen* q;

	bool valid1 = (this->_row - row) == 1 && this->_col - col == 0 && !this->_boardPtr->isEmpty(row, col) == 0 && this->getColor() == BLACK;

	bool valid2 = (this->_row - row) == 1 && abs(this->_col - col) == 1 && !this->_boardPtr->isEmpty(row, col) == 1 && this->getColor() == BLACK;

	bool valid3 = (this->_row - row) == -1 && this->_col - col == 0 && !this->_boardPtr->isEmpty(row, col) == 0 && this->getColor() == WHITE;

	bool valid4 = (this->_row - row) == -1 && abs(this->_col - col) == 1 && !this->_boardPtr->isEmpty(row, col) == 1 && this->getColor() == WHITE;

	bool valid5 = (this->_row - row) == -2 && this->_col - col == 0 && !this->_boardPtr->isEmpty(row, col) == 0 && this->getColor() == WHITE && this->_isFirstMove;

	bool valid6 = (this->_row - row) == 2 && this->_col - col == 0 && !this->_boardPtr->isEmpty(row, col) == 0 && this->getColor() == BLACK && this->_isFirstMove;

	bool valid7 = ((this->_row - row == 0 ) && (abs(this->_col - col) == 1) && 
		(this->_boardPtr->isEmpty(row - 1, col)) && (this->getColor() == BLACK) &&
		(this->_boardPtr->isEmpty(3, col) == false) && 
		(this->_boardPtr->_figuresArr[3][col]->getColor() == WHITE) &&
		(this->_boardPtr->_figuresArr[3][col]->getType() == PAWN) &&
		(this->_boardPtr->_figuresArr[3][col]->getColor() == !this->_color) &&
		(dynamic_cast<Pawn*>(this->_boardPtr->_figuresArr[3][col])->isFirstMove2Rows()));

	bool valid8 = ((this->_row - row == 0) && (abs(this->_col - col) == 1) && 
		(this->_boardPtr->isEmpty(row + 1, col)) && (this->getColor() == WHITE) &&
		(this->_boardPtr->isEmpty(4, col) == false) && 
		(this->_boardPtr->_figuresArr[4][col]->getColor() == BLACK) &&
		(this->_boardPtr->_figuresArr[4][col]->getType() == PAWN) &&
		(this->_boardPtr->_figuresArr[4][col]->getColor() == !this->_color) && 
		(dynamic_cast<Pawn*>(this->_boardPtr->_figuresArr[4][col])->isFirstMove2Rows()));

	if (valid1 || valid2 || valid3 || valid4 || valid5 || valid6)
	{
		if (this->_isFirstMove == true && abs(this->_row - row) == 2)
		{
			this->_firstMove2Rows = true;
		}
		if (row == SIZE - 1 && this->_color == WHITE ||
			row == 0 && this->_color == BLACK)
		{
			q = new Queen(row, col, this->_color, this->_boardPtr);
			this->_newFigure = q;
			return VALID_MOVE;
		}
		this->_isFirstMove = false;
		this->_row = row;
		this->_col = col;
		return VALID_MOVE;
	}
	if (valid7)
	{
		delete this->_boardPtr->_figuresArr[3][col];
		this->_boardPtr->_figuresArr[3][col] = nullptr;
		this->_boardPtr->_whiteOrBlack = !this->_boardPtr->_whiteOrBlack; // give the next move to the same team
		this->_boardPtr->_isEnPassent = true;
		this->_boardPtr->_enPassentDstCol = col;
		this->_boardPtr->_enPassentDstRow = 2;
		this->_boardPtr->_enPassentSrcCol = col;
		this->_boardPtr->_enPassentSrcRow = 3;
		return VALID_MOVE;
	}
	if (valid8)
	{
		delete this->_boardPtr->_figuresArr[4][col];
		this->_boardPtr->_figuresArr[4][col] = nullptr;
		this->_boardPtr->_whiteOrBlack = !this->_boardPtr->_whiteOrBlack; // give the next move to the same team
		this->_boardPtr->_isEnPassent = true;
		this->_boardPtr->_enPassentDstCol = col;
		this->_boardPtr->_enPassentDstRow = 5;
		this->_boardPtr->_enPassentSrcCol = col;
		this->_boardPtr->_enPassentSrcRow = 4;
		return VALID_MOVE;
	}
	return ILLEGAL_MOVE;
}

bool Pawn::isFirstMove2Rows() const
{
	return this->_firstMove2Rows;
}

Figure* Pawn::getNewFigure() const
{
	return this->_newFigure;
}
