#include "Board.h"

class Board;
int Board::_numOfBoards = 0;


// CTOR
Board::Board(std::string toolsMap)
{
	char figure;
	this->_whiteKingCol = 3;
	this->_whiteKingRow = 0;
	this->_blackKingCol = 3;
	this->_blackKingRow = 7;
	this->_whiteOrBlack = (int)toolsMap[COLOR_INDEX];
	toolsMap.pop_back();
	//std::reverse(toolsMap.begin(), toolsMap.end());
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{	
			figure = toolsMap[(SIZE - i - 1) * SIZE + j];
			this->_figuresArr[i][j] = this->charToFigure(figure , i, j);
			if (this->_figuresArr[i][j] != nullptr && this->_figuresArr[i][j]->getColor() == WHITE)
			{
				this->_whiteFigures.push_back(i);
				this->_whiteFigures.push_back(j);
			}
			else
			{
				this->_blackFigures.push_back(i);
				this->_blackFigures.push_back(j);
			}
		}
	}

}

Board Board::getBoard(std::string toolsMap)
{
	if (Board::_numOfBoards)
	{
		throw(std::string("ERROR: Too many boards"));
	}
	Board::_numOfBoards++;
	return Board::Board(toolsMap);
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
	srcFigure = this->getSrcFigure(srcRow, srcCol);
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
		this->_figuresArr[dstRow][dstCol] = srcFigure;
		this->_figuresArr[srcRow][srcCol] = nullptr;
		code = this->isShah((this->_whiteOrBlack)) == true ? MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM : VALID_MOVE;
		if (code == MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM)
		{
			this->_figuresArr[dstRow][dstCol] = dstFigure;
			this->_figuresArr[srcRow][srcCol] = srcFigure;
			srcFigure->setLocation(srcRow, srcCol);
			return MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM;
		}
	}
	if (code == VALID_MOVE)
	{
//		dstFigure = this->_figuresArr[dstRow][dstCol];
		delete dstFigure; 
//		this->_figuresArr[dstRow][dstCol] = srcFigure;
//		this->_figuresArr[srcRow][srcCol] = nullptr;
		this->_whiteOrBlack = !this->_whiteOrBlack;
		code = this->isShah(this->_whiteOrBlack) == true ? VALID_MOVE_SHAH_ON_OPPONENT : VALID_MOVE;
	}
	std::cout << "The code is: " << code << std::endl;
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

bool Board::isShah(const bool blackOrWhite )
{
	//std::vector<int> figures;
	int i, j, size, kingRow, kingCol, row, col, tmpCol, tmpRow;
	if (blackOrWhite == BLACK)
	{
		kingRow = this->_blackKingRow;
		kingCol = this->_blackKingCol;
	}
	else
	{
		kingRow = this->_whiteKingRow;
		kingCol = this->_whiteKingCol;
	}
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (this->_figuresArr[i][j] != nullptr)
			{
				tmpCol = this->_figuresArr[i][j]->getCol();
				tmpRow = this->_figuresArr[i][j]->getRow();
				if (this->_figuresArr[i][j]->getColor() != blackOrWhite && this->_figuresArr[i][j]->isValidMove(kingRow, kingCol) == VALID_MOVE)
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

