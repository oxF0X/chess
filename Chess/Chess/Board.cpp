#include "Board.h"

class Board;
int Board::_numOfBoards = 0;


std::string Board::createBoardMap() const
{
	std::string map = "";
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (this->_figuresArr[SIZE - i - 1][j] == nullptr)
			{
				map += '#';
			}
			else if(this->_figuresArr[SIZE - i - 1][j]->getColor() == BLACK)
			{ 
				map += this->_figuresArr[SIZE - i - 1][j]->getType();
			}
			else
			{
				map += toupper(this->_figuresArr[SIZE - i - 1][j]->getType());
			}
		}
	}
	map += char(!this->_whiteOrBlack) + ZERO_ASCII_CODE;
	return map;
}

// CTOR
Board::Board(Pipe* p, std::string toolsMap)
{
	char figure;
	this->_whiteOrBlack = (int)toolsMap[COLOR_INDEX];
	toolsMap.pop_back();
	this->_isCastling = false;
	this->_p = p;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{	
			figure = toolsMap[(SIZE - i - 1) * SIZE + j];
			//figure = toolsMap[i +  SIZE + j];
			this->_figuresArr[i][j] = this->charToFigure(figure , i, j);
			if (figure == toupper(KING))
			{
				this->_whiteKingCol = j;
				this->_whiteKingRow = i;
			}
			if (figure == KING)
			{
				this->_blackKingCol = j;
				this->_blackKingRow = i;
			}
		}
	}
}

Board Board::getBoard(Pipe* p, std::string toolsMap)
{
	if (Board::_numOfBoards)
	{
		throw(std::string("ERROR: Too many boards"));
	}
	Board::_numOfBoards++;
	return Board::Board(p, toolsMap);
}

int Board::move(std::string location)
{
	int code;
	Figure* srcFigure = nullptr;
	Figure* dstFigure = nullptr;    
	int srcCol = ((int)(location[0])) - A_ASCII_CODE;		// translate location to int
	int srcRow = ((int)location[1]) - ONE_ASCII_CODE;
	int dstCol = ((int)(location[2])) - A_ASCII_CODE;
	int dstRow = ((int)location[3]) - ONE_ASCII_CODE;
	int tmpKingCol = this->_whiteOrBlack == WHITE ? this->_whiteKingCol : this->_blackKingCol;
	int tmpKingRow = this->_whiteOrBlack == WHITE ? this->_whiteKingRow : this->_blackKingRow;
	int kingRow;
	int kingCol;
	srcFigure = this->getSrcFigure(srcRow, srcCol);
	if (this->_isCastling)
	{
		if (srcCol != this->_castlingSrcCol || srcRow != this->_castlingSrcRow || dstCol != this->_castlingDstCol || dstRow != this->_castlingDstRow)
		{
			return ILLEGAL_MOVE;
		}
		this->_figuresArr[dstRow][dstCol] = this->_figuresArr[srcRow][srcCol];
		this->_figuresArr[srcRow][srcCol] = nullptr;
		this->_isCastling = false;
		this->_whiteOrBlack = !this->_whiteOrBlack;
		this->_figuresArr[dstRow][dstCol]->setLocation(dstRow, dstCol);
		return VALID_MOVE;
	}
	if (srcFigure == nullptr)
	{
		return INVALID_SRC_FIGURE;
	}
	if (this->checkDst(dstRow, dstCol) == TEAM_FIGURE_ON_DST_LOCATION)
	{
		return TEAM_FIGURE_ON_DST_LOCATION;
	}
	code = srcFigure->isValidMove(dstRow, dstCol);
	if (code == VALID_MOVE)
	{
		dstFigure = this->_figuresArr[dstRow][dstCol];
		if (this->_figuresArr[srcRow][srcCol]->getType() == PAWN)
		{
			this->_figuresArr[dstRow][dstCol] = dynamic_cast<Pawn*>(this->_figuresArr[srcRow][srcCol])->getNewFigure();
		}
		if(this->_figuresArr[dstRow][dstCol] == nullptr || this->_figuresArr[srcRow][srcCol]->getType() != PAWN)
		{
			this->_figuresArr[dstRow][dstCol] = srcFigure;
		}
		this->_figuresArr[srcRow][srcCol] = nullptr;
		if (this->_whiteOrBlack == BLACK)
		{
			kingRow = this->_blackKingRow;
			kingCol = this->_blackKingCol;
		}
		else
		{
			kingRow = this->_whiteKingRow;
			kingCol = this->_whiteKingCol;
		}
		code = this->isShah(this->_whiteOrBlack, kingRow, kingCol) == true ? MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM : VALID_MOVE;
		if (code == MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM)
		{
			this->_isCastling = false;
			this->_figuresArr[dstRow][dstCol] = dstFigure;
			this->_figuresArr[srcRow][srcCol] = srcFigure;
			srcFigure->setLocation(srcRow, srcCol);
			if (this->_whiteOrBlack == WHITE)
			{
				this->_whiteKingCol = tmpKingCol;
				this->_whiteKingRow = tmpKingRow;
				return MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM;
			}
			this->_blackKingCol = tmpKingCol;
			this->_blackKingRow = tmpKingRow;
			return MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM;
		}

		delete dstFigure;
		
		if (this->_whiteOrBlack == WHITE)
		{
			kingRow = this->_blackKingRow;
			kingCol = this->_blackKingCol;
		}
		else
		{
			kingRow = this->_whiteKingRow;
			kingCol = this->_whiteKingCol;
		}
		code = this->isShah(!this->_whiteOrBlack, kingRow, kingCol) == true ? VALID_MOVE_SHAH_ON_OPPONENT : VALID_MOVE;
		this->_whiteOrBlack = !this->_whiteOrBlack;
	}
	return code;

}


Figure* Board::getSrcFigure(int& row, int& col) const
{
	Figure* newFigure = nullptr;
	if (this->isEmpty(row, col) || (this->_figuresArr[row][col])->getColor() != this->_whiteOrBlack)
	{
		return newFigure;
	}
	return this->_figuresArr[row][col];
}

int Board::checkDst(int& row, int& col) const
{
	Figure* newFigure = nullptr;
	if (this->isEmpty(row, col) || this->_figuresArr[row][col]->getColor() != this->_whiteOrBlack)
	{
		return VALID_MOVE;
	}
	return TEAM_FIGURE_ON_DST_LOCATION;
}

bool Board::isShah(const bool blackOrWhite, int row, int col)
{
	int i, j, size, kingRow, kingCol, tmpCol, tmpRow;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (this->_figuresArr[i][j] != nullptr)
			{
				tmpCol = this->_figuresArr[i][j]->getCol();
				tmpRow = this->_figuresArr[i][j]->getRow();
				if (this->_figuresArr[i][j]->getColor() != blackOrWhite && this->_figuresArr[i][j]->isValidMove(row, col) == VALID_MOVE)
				{
					this->_figuresArr[i][j]->setLocation(tmpRow, tmpCol);
					return true;
				}
			}
		}
	}
	return false;
}

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


bool Board::isEmpty(int row, int col) const
{
	return this->_figuresArr[row][col] == nullptr;
}

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

