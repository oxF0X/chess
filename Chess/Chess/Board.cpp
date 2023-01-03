#include "Board.h"

class Board;
int Board::_numOfBoards = 0;


// CTOR
Board::Board(std::string toolsMap)
{
	char figure;
	this->_whiteOrBlack = (int)toolsMap[COLOR_INDEX];
	toolsMap.pop_back();
	this->_isCastling = false;
	this->_isEnPassent = false;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{	
			figure = toolsMap[(SIZE - i - 1) * SIZE + j]; // get char in index col and opposite row
			this->_figuresArr[i][j] = this->charToFigure(figure , i, j);
			if (figure == toupper(KING)) // setting white king's location
			{
				this->_whiteKingCol = j;
				this->_whiteKingRow = i;
			}
			if (figure == KING)
			{
				this->_blackKingCol = j; // setting black king's locatio
				this->_blackKingRow = i;
			}
		}
	}
}

void Board::getKingRowAndCol(bool color, int* row, int* col) const
{
	if (color == WHITE) // setting white king's location
	{
		*col = this->_whiteKingCol;
		*row = this->_whiteKingRow;
		return;
	}

	*col  = this->_blackKingCol; // setting black king's locatio
	*row = this->_blackKingRow;
}

// Create a board object if there isn't any board yet
Board Board::getBoard(std::string toolsMap)
{
	if (Board::_numOfBoards)
	{
		throw(std::string("ERROR: Too many boards"));
	}
	Board::_numOfBoards++;
	return Board::Board(toolsMap);
}


// Moves figure on the board (if the move is valid) and returns a move code
int Board::move(std::string location)
{
	Figure* srcFigure = nullptr;
	Figure* dstFigure = nullptr; 
	int srcCol = ((int)(location[0])) - A_ASCII_CODE; // translate location letter to int
	int srcRow = ((int)location[1]) - ONE_ASCII_CODE; // traanslate cahr to int
	int dstCol = ((int)(location[2])) - A_ASCII_CODE;
	int dstRow = ((int)location[3]) - ONE_ASCII_CODE;
	int kingRow, kingCol, code;

	if (this->_isCastling) // _isCastling == true, the user began a castling process by mooving the king two cols and now he must place the rook in the correct place
	{   // rook castling col and row saved in this->_castlingSrcCol and this->_castlingSrcRow if the location from the gui equals to them than the move must be valid.
		if (srcCol != this->_castlingSrcCol || srcRow != this->_castlingSrcRow || dstCol != this->_castlingDstCol || dstRow != this->_castlingDstRow) 
		{
			return ILLEGAL_MOVE;
		}
		this->_figuresArr[dstRow][dstCol] = this->_figuresArr[srcRow][srcCol]; // switching figures in array 
		this->_figuresArr[srcRow][srcCol] = nullptr;
		this->_isCastling = false; // castling process is finished
		this->_whiteOrBlack = !this->_whiteOrBlack; // next turn
		this->_figuresArr[dstRow][dstCol]->setLocation(dstRow, dstCol); // changes rook object's location
		return VALID_MOVE;
	}

	if (this->_isEnPassent) // _isEnPassen == true, the user began an enpassent process, to fix the GUI the user has to eat "correctly" the pawn and than move it to it's real place
	{
		if (srcCol != this->_enPassentSrcCol || srcRow != this->_enPassentSrcRow || dstCol != this->_enPassentDstCol || dstRow != this->_enPassentDstRow)
		{
			return ILLEGAL_MOVE;
		}
		this->_figuresArr[dstRow][dstCol] = this->_figuresArr[srcRow][srcCol]; // switching figures in array 
		this->_figuresArr[srcRow][srcCol] = nullptr;
		this->_isEnPassent = false; // castling process is finished
		this->_whiteOrBlack = !this->_whiteOrBlack; // next turn
		this->_figuresArr[dstRow][dstCol]->setLocation(dstRow, dstCol); // changes rook object's location
		return VALID_MOVE;
	}
	srcFigure = this->getSrcFigure(srcRow, srcCol); // get the figure that is going to be moved
	if (srcFigure == nullptr) // if no source than nothiing to move
	{
		return INVALID_SRC_FIGURE;
	}
	if (this->checkDst(dstRow, dstCol) == TEAM_FIGURE_ON_DST_LOCATION) // check if dst doesn't contain team's figure
	{
		return TEAM_FIGURE_ON_DST_LOCATION;
	}

	code = srcFigure->isValidMove(dstRow, dstCol);
	if (code == VALID_MOVE)
	{
		dstFigure = this->_figuresArr[dstRow][dstCol]; // switching figures in array 
		if (this->_figuresArr[srcRow][srcCol]->getType() == PAWN) // if PAWN than there is possibility that he reached the end of the board and became a queen
		{
			this->_figuresArr[dstRow][dstCol] = dynamic_cast<Pawn*>(this->_figuresArr[srcRow][srcCol])->getNewFigure(); // check if the pawn genarated a new figure
			if (this->_figuresArr[dstRow][dstCol] != nullptr) // if there is a new figure than we need to swich pawn to the new figure
			{
				delete this->_figuresArr[srcRow][srcCol];
				this->_figuresArr[srcRow][srcCol] = nullptr;
			}
			else
			{
				this->_figuresArr[dstRow][dstCol] = srcFigure; // pawn didn't reach the end of the board
			}
		}
		else if(this->_figuresArr[srcRow][srcCol]->getType() != PAWN) // if not pawn than just move figures to the correct places
		{
			this->_figuresArr[dstRow][dstCol] = srcFigure;
		}
		this->_figuresArr[srcRow][srcCol] = nullptr;

		this->getKingRowAndCol(this->_whiteOrBlack, &kingRow, &kingCol);

		code = this->isShah(this->_whiteOrBlack, kingRow, kingCol) == true ? MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM : VALID_MOVE;
		if (code == MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM)
		{
			this->_figuresArr[dstRow][dstCol] = dstFigure; // return the figure to it's previous places
			this->_figuresArr[srcRow][srcCol] = srcFigure;
			srcFigure->setLocation(srcRow, srcCol);
			return MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM;
		}

		delete dstFigure; // no need for dst figure
		this->getKingRowAndCol(!this->_whiteOrBlack, &kingRow, &kingCol);
		if (this->isShah(!this->_whiteOrBlack, kingRow, kingCol) == true) // checking if the move couse shah to the other playes
		{
			code = VALID_MOVE_SHAH_ON_OPPONENT;
			if (this->isCheckmate(!this->_whiteOrBlack))
			{
				code = CHECKMATE;
			}
			this->_figuresArr[kingRow][kingCol]->setLocation(kingRow, kingCol);
		}
		else
		{
			code = VALID_MOVE;
		}
		this->_whiteOrBlack = !this->_whiteOrBlack; // switch turn
	}
	return code;

}


// this function gets row and col and check if the figure on that location is a valid src figure
Figure* Board::getSrcFigure(int& row, int& col) const
{
	Figure* newFigure = nullptr;
	if (this->isEmpty(row, col) || (this->_figuresArr[row][col])->getColor() != this->_whiteOrBlack)
	{
		return newFigure;
	}
	return this->_figuresArr[row][col];
}

// this function gets row and col and check if the figure on that location is a valid dst figure
int Board::checkDst(int& row, int& col) const
{
	Figure* newFigure = nullptr;
	if (this->isEmpty(row, col) || this->_figuresArr[row][col]->getColor() != this->_whiteOrBlack)
	{
		return VALID_MOVE;
	}
	return TEAM_FIGURE_ON_DST_LOCATION;
}

// check if there is shah on the king
bool Board::isShah(const bool blackOrWhite, int row, int col)
{
	int i, j, size, kingRow, kingCol, tmpCol, tmpRow;
	bool isShah = false, rook, pawn, king;
	this->_attackingFigures.clear();
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (this->_figuresArr[i][j] != nullptr && this->_figuresArr[i][j]->getColor() != blackOrWhite)
			{
				tmpCol = this->_figuresArr[i][j]->getCol();
				tmpRow = this->_figuresArr[i][j]->getRow();

				pawn = false;
				king = false;
				rook = false;
			
				if(this->_figuresArr[i][j]->getType() == PAWN && dynamic_cast<Pawn*>(this->_figuresArr[i][j])->isFirstMove())
				{
					pawn = true;
				}
				else if (this->_figuresArr[i][j]->getType() == ROOK && dynamic_cast<Rook*>(this->_figuresArr[i][j])->isFirstMove())
				{
					rook - true;
				}
				else if (this->_figuresArr[i][j]->getType() == KING && dynamic_cast<King*>(this->_figuresArr[i][j])->isFirstMove())
				{
					king = true;
				}
				if (this->_figuresArr[i][j]->isValidMove(row, col) == VALID_MOVE)
				{
					this->_figuresArr[i][j]->setLocation(tmpRow, tmpCol);
					this->_attackingFigures.push_back(this->_figuresArr[i][j]);
					if (this->_figuresArr[i][j]->getType() == PAWN)
					{
						dynamic_cast<Pawn*>(this->_figuresArr[i][j])->setFirstMove(pawn);
					}
					if (this->_figuresArr[i][j]->getType() == ROOK)
					{
						dynamic_cast<Rook*>(this->_figuresArr[i][j])->setFirstMove(rook);
					}
					if (this->_figuresArr[i][j]->getType() == KING)
					{
						dynamic_cast<King*>(this->_figuresArr[i][j])->setFirstMove(king);
					}
					isShah = true;
				}
			}
		}
	}
	return isShah;
}

// translates characted to a figure
Figure* Board::charToFigure(char f, const int& row, const int& col)
{
	Figure* newFigure = nullptr;
	switch (tolower(f))
	{
	case KING:
		if (isupper(f))
		{
			newFigure = new King(row, col, WHITE, this);
			break;
		}
		newFigure = new King(row, col, BLACK, this);
		break;

	case QUEEN:
		if (isupper(f))
		{
			newFigure = new Queen(row, col, WHITE, this);
			break;
		}
		newFigure = new Queen(row, col, BLACK, this);
		break;

	case BISHOP:
		if (isupper(f))
		{
			newFigure = new Bishop(row, col, WHITE, this);
			break;
		}
		newFigure = new Bishop(row, col, BLACK, this);
		break;

	case ROOK:
		if (isupper(f))
		{
			newFigure = new Rook(row, col, WHITE, this);
			break;
		}
		newFigure = new Rook(row, col, BLACK, this);
		break;

	case PAWN:
		if (isupper(f))
		{
			newFigure = new Pawn(row, col, WHITE, this);
			break;
		}
		newFigure = new Pawn(row, col, BLACK, this);
		break;

	case KNIGHT:
		if (isupper(f))
		{
			newFigure = new Kinght(row, col, WHITE, this);
			break;
		}
		newFigure = new Kinght(row, col, BLACK, this);
		break;

	default:
		break;

	}
	return newFigure;
}

// returns if the location is empty
bool Board::isEmpty(int row, int col) const
{
	return row > SIZE - 1 || col > SIZE - 1 || row < 0 || col < 0 || this->_figuresArr[row][col] == nullptr;
}

// sets the king location
void Board::setKingLocation(const int& row, const int& col, bool color)
{
	if (color == WHITE)
	{
		this->_whiteKingRow = row;
		this->_whiteKingCol = col;
		return;
	}
	this->_blackKingRow = row;
	this->_blackKingCol = col;
}


// DTOR
Board::~Board()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			delete this->_figuresArr[i][j];
		}
	}
}


bool Board::isCheckmate(const bool color)
{
	int kingRow, kingCol, i, j, k, l, tmpRow, tmpCol, lower, bigger, size = this->_attackingFigures.size(), tmp1, tmp2;
	Figure* attackingFigure = this->_attackingFigures[0];
	Figure* src = nullptr;
    Figure*	dst = nullptr;
	bool king, pawn, rook;
	this->getKingRowAndCol(!this->_whiteOrBlack, &kingRow, &kingCol);

	if ((this->isEmpty(kingRow - 1, kingCol + 1) || this->_figuresArr[kingRow - 1][kingCol + 1]->getColor() != color) &&
		(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow - 1, kingCol + 1) == VALID_MOVE && (this->isShah(color, kingRow - 1, kingCol + 1)) == false) ||

		((this->isEmpty(kingRow + 1, kingCol) || this->_figuresArr[kingRow + 1][kingCol]->getColor() != color) && 
			(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow + 1, kingCol) == VALID_MOVE && (this->isShah(color, kingRow + 1, kingCol) == false))) ||
		
		((this->isEmpty(kingRow - 1, kingCol) || this->_figuresArr[kingRow - 1][kingCol]->getColor() != color) &&
			(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow - 1, kingCol) == VALID_MOVE && (this->isShah(color, kingRow - 1, kingCol) == false))) ||

		((this->isEmpty(kingRow + 1, kingCol + 1) || this->_figuresArr[kingRow + 1][kingCol + 1]->getColor() != color) &&
			(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow + 1, kingCol + 1) == VALID_MOVE && (this->isShah(color, kingRow + 1, kingCol + 1) == false))) ||

		((this->isEmpty(kingRow - 1, kingCol - 1) || this->_figuresArr[kingRow - 1][kingCol - 1]->getColor() != color) &&
			(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow - 1, kingCol - 1) == VALID_MOVE && (this->isShah(color, kingRow - 1, kingCol - 1) == false))) ||

		((this->isEmpty(kingRow, kingCol + 1) || this->_figuresArr[kingRow][kingCol + 1]->getColor() != color) && 
			(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow, kingCol + 1) == VALID_MOVE && (this->isShah(color, kingRow, kingCol + 1) == false)))  ||

		((this->isEmpty(kingRow, kingCol - 1) || this->_figuresArr[kingRow][kingCol - 1]->getColor() != color) &&
			(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow, kingCol - 1) == VALID_MOVE && (this->isShah(color, kingRow, kingCol - 1) == false))) ||
		
		((this->isEmpty(kingRow + 1, kingCol - 1) || this->_figuresArr[kingRow + 1][kingCol - 1]->getColor() != color) &&
			(this->_figuresArr[kingRow][kingCol]->isValidMove(kingRow + 1, kingCol - 1) == VALID_MOVE && (this->isShah(color, kingRow + 1, kingCol - 1) == false))))
	{
		this->_figuresArr[kingRow][kingCol]->setLocation(kingRow, kingCol);
		return false;
	}
	this->_figuresArr[kingRow][kingCol]->setLocation(kingRow, kingCol);

	for (i = 0; i < SIZE; i++) //check if we can eat the attacking figure
	{
		for (j = 0; j < SIZE; j++)
		{
			if (this->_figuresArr[i][j] != nullptr)
			{
				tmpCol = this->_figuresArr[i][j]->getCol();
				tmpRow = this->_figuresArr[i][j]->getRow();

				dst = this->_figuresArr[attackingFigure->getRow()][attackingFigure->getCol()];
				src = this->_figuresArr[i][j];

				pawn = false;
				king = false;
				rook = false;

				if (src->getType() == PAWN && dynamic_cast<Pawn*>(src)->isFirstMove())
				{
					pawn = true;
				}
				else if (src->getType() == ROOK && dynamic_cast<Rook*>(src)->isFirstMove())
				{
					rook - true;
				}
\
				if (this->_figuresArr[i][j]->getType() != KING && this->_figuresArr[i][j]->getColor() == color && j != attackingFigure->getCol() && i != attackingFigure->getRow() && this->_figuresArr[i][j]->isValidMove(attackingFigure->getRow(), attackingFigure->getCol()) == VALID_MOVE)
				{
					this->_figuresArr[attackingFigure->getRow()][attackingFigure->getCol()] = this->_figuresArr[i][j];
					this->_figuresArr[i][j] = nullptr;
					if (src->getType() == PAWN)
					{
						dynamic_cast<Pawn*>(this->_figuresArr[i][j])->setFirstMove(pawn);
					}
					if (src->getType() == ROOK)
					{
						dynamic_cast<Rook*>(this->_figuresArr[i][j])->setFirstMove(rook);
					}

					if (this->isShah(color, kingRow, kingCol) == false)
					{
						this->_figuresArr[attackingFigure->getRow()][attackingFigure->getCol()] = dst;
						this->_figuresArr[i][j] = src;
						this->_figuresArr[i][j]->setLocation(tmpRow, tmpCol);
						return false;
					}
					this->_figuresArr[attackingFigure->getRow()][attackingFigure->getCol()] = dst;
					this->_figuresArr[i][j] = src;
					this->_figuresArr[i][j]->setLocation(tmpRow, tmpCol);
				}
			}
		}
	}

	if (attackingFigure->getType() == KNIGHT || size > 1) // if there is more than one attacking figures its a shah or if its knight
	{
		return true;
	}

	if (kingRow == attackingFigure->getRow()) // check if we can put figure berween the king and the attacking figure
	{
		lower = kingRow < attackingFigure->getRow() ? kingRow : attackingFigure->getRow();
		bigger = lower + abs(kingRow - attackingFigure->getRow());
		for (i = lower; i < bigger; i++)
		{
			for (j = 0; j < SIZE; j++)
			{
				for (k = 0; k < SIZE; k++)
				{
					if (this->_figuresArr[j][k] != nullptr)
					{

						tmpCol = this->_figuresArr[j][k]->getCol();
						tmpRow = this->_figuresArr[j][k]->getRow();

						dst = this->_figuresArr[i][attackingFigure->getCol()];
						src = this->_figuresArr[j][k];
						this->_figuresArr[i][attackingFigure->getCol()] = this->_figuresArr[j][k];
						this->_figuresArr[j][k] = nullptr;

						pawn = false;
						king = false;
						rook = false;

						if (src->getType() == PAWN && dynamic_cast<Pawn*>(src)->isFirstMove())
						{
							pawn = true;
						}
						else if (src->getType() == ROOK && dynamic_cast<Rook*>(src)->isFirstMove())
						{
							rook - true;
						}
						if (src->getType() != KING && src->getColor() == color && src->getType() != KING && src->isValidMove(i, attackingFigure->getCol()) == VALID_MOVE)
						{ 
							if (src->getType() == PAWN)
							{
								dynamic_cast<Pawn*>(this->_figuresArr[i][j])->setFirstMove(pawn);
							}
							if (src->getType() == ROOK)
							{
								dynamic_cast<Rook*>(this->_figuresArr[i][j])->setFirstMove(rook);
							}
							if (this->isShah(color, kingRow, kingCol) == false)
							{
								this->_figuresArr[i][attackingFigure->getCol()] = dst;
								this->_figuresArr[j][k] = src;
								this->_figuresArr[j][k]->setLocation(tmpRow, tmpCol);
								return false;
							}
						}
						this->_figuresArr[i][attackingFigure->getCol()] = dst;
						this->_figuresArr[j][k] = src;
						this->_figuresArr[j][k]->setLocation(tmpRow, tmpCol);
					}
				}
			}
		}
	}
	if (kingCol == attackingFigure->getCol())
	{
		lower = kingRow < attackingFigure->getRow() ? kingRow : attackingFigure->getRow();
		bigger = lower + abs(kingRow - attackingFigure->getRow());
		for (i = lower; i < bigger; i++)
		{
			for (j = 0; j < SIZE; j++)
			{
				for (k = 0; k < SIZE; k++)
				{
					if (this->_figuresArr[j][k] != nullptr)
					{
						tmpCol = this->_figuresArr[j][k]->getCol();
						tmpRow = this->_figuresArr[j][k]->getRow();
						dst = this->_figuresArr[attackingFigure->getRow()][i];
						src = this->_figuresArr[j][k];
						this->_figuresArr[attackingFigure->getRow()][i] = this->_figuresArr[j][k];
						this->_figuresArr[j][k] = nullptr;

						if (src->getType() == PAWN && dynamic_cast<Pawn*>(src)->isFirstMove())
						{
							pawn = true;
						}
						else if (src->getType() == ROOK && dynamic_cast<Rook*>(src)->isFirstMove())
						{
							rook - true;
						}

						if (src->getType() != KING && src->getColor() == color && src->getType() != KING && src->isValidMove(attackingFigure->getRow(), i) == VALID_MOVE)
						{
							if (src->getType() == PAWN)
							{
								dynamic_cast<Pawn*>(this->_figuresArr[i][j])->setFirstMove(pawn);
							}
							if (src->getType() == ROOK)
							{
								dynamic_cast<Rook*>(this->_figuresArr[i][j])->setFirstMove(rook);
							}
							if (this->isShah(color, kingRow, kingCol) == false)
							{
								this->_figuresArr[attackingFigure->getRow()][i] = dst;
								this->_figuresArr[j][k] = src;
								this->_figuresArr[j][k]->setLocation(tmpRow, tmpCol);
								return false;
							}
						}
						this->_figuresArr[attackingFigure->getRow()][i] = dst;
						this->_figuresArr[j][k] = src;
						this->_figuresArr[j][k]->setLocation(tmpRow, tmpCol);
					}
				}
			}
		}
	}

	if (kingRow < attackingFigure->getRow())
	{
		tmpCol = kingRow;
	}
	else
	{
		tmpCol = attackingFigure->getRow();
	}
	if (tmpCol == attackingFigure->getRow())
	{
		lower = kingRow < attackingFigure->getRow() ? kingRow : attackingFigure->getRow();
		bigger = lower + abs(kingRow - attackingFigure->getRow());
		for (i = lower + 1, j = kingRow + 1; i < bigger; i++, j++)
		{
			for (k = 0; k < SIZE; k++)
			{
				for (l = 0; l < SIZE; l++)
				{
					if (this->_figuresArr[k][l] != nullptr)
					{

						tmpCol = this->_figuresArr[k][l]->getCol();
						tmpRow = this->_figuresArr[k][l]->getRow();
						dst = this->_figuresArr[i][j];
						src = this->_figuresArr[k][l];
						this->_figuresArr[attackingFigure->getRow()][attackingFigure->getCol()] = this->_figuresArr[j][k];
						this->_figuresArr[j][k] = nullptr;

						if (src->getType() == PAWN && dynamic_cast<Pawn*>(src)->isFirstMove())
						{
							pawn = true;
						}
						else if (src->getType() == ROOK && dynamic_cast<Rook*>(src)->isFirstMove())
						{
							rook - true;
						}

						if (src->getType() != KING && src->getColor() == color && src->getType() != KING && src->isValidMove(i, j) == VALID_MOVE)
						{
							if (src->getType() == PAWN)
							{
								dynamic_cast<Pawn*>(this->_figuresArr[i][j])->setFirstMove(pawn);
							}
							if (src->getType() == ROOK)
							{
								dynamic_cast<Rook*>(this->_figuresArr[i][j])->setFirstMove(rook);
							}
							if (this->isShah(color, kingRow, kingCol) == false)
							{
								this->_figuresArr[i][j] = dst;
								this->_figuresArr[k][l] = src;
								this->_figuresArr[k][l]->setLocation(tmpRow, tmpCol);
							}

							return false;
						}
						this->_figuresArr[i][j] = dst;
						this->_figuresArr[k][l] = src;
						this->_figuresArr[k][l]->setLocation(tmpRow, tmpCol);
					}
				}
			}
		}
	}
	else
	{
		lower = kingRow < attackingFigure->getRow() ? kingRow : attackingFigure->getRow();
		bigger = lower + abs(kingRow - attackingFigure->getRow());
		for (i = lower + 1, j = kingCol - 1; i < bigger; i++, j--)
		{
			for (k = 0; k < SIZE; k++)
			{
				for (l = 0; l < SIZE; l++)
				{
					if (this->_figuresArr[k][l] != nullptr)
					{

						tmpCol = this->_figuresArr[k][l]->getCol();
						tmpRow = this->_figuresArr[k][l]->getRow();
						dst = this->_figuresArr[i][j];
						src = this->_figuresArr[k][l];
						this->_figuresArr[attackingFigure->getRow()][attackingFigure->getCol()] = this->_figuresArr[j][k];
						this->_figuresArr[j][k] = nullptr;

						if (src->getType() == PAWN && dynamic_cast<Pawn*>(src)->isFirstMove())
						{
							pawn = true;
						}
						else if (src->getType() == ROOK && dynamic_cast<Rook*>(src)->isFirstMove())
						{
							rook - true;
						}

						if (src->getType() != KING && src->getColor() == color && src->getType() != KING && src->isValidMove(i, j) == VALID_MOVE)
						{
							if (src->getType() == PAWN)
							{
								dynamic_cast<Pawn*>(this->_figuresArr[i][j])->setFirstMove(pawn);
							}
							if (src->getType() == ROOK)
							{
								dynamic_cast<Rook*>(this->_figuresArr[i][j])->setFirstMove(rook);
							}
							if (this->isShah(color, kingRow, kingCol) == false)
							{
								this->_figuresArr[i][j] = dst;
								this->_figuresArr[k][l] = src;
								this->_figuresArr[k][l]->setLocation(tmpRow, tmpCol);
								return false;
							}
						}
						this->_figuresArr[i][j] = dst;
						this->_figuresArr[k][l] = src;
						this->_figuresArr[k][l]->setLocation(tmpRow, tmpCol);
					}
				}
			}
		}
	}
	return true;
}


