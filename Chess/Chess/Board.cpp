#include "Board.h"

class Board;
int Board::_numOfBoards = 0;


// CTOR
Board::Board(std::string toolsMap)
{
	char color;
	this->_whiteKingCol = 3;
	this->_whiteKingRow = 0;
	this->_blackKingCol = 3;
	this->_whiteKingRow = 7;
	this->_whiteOrBlack = (int)toolsMap[COLOR_INDEX];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{	
			color = toolsMap[i * SIZE + j];
			this->_figuresArr[i][j] = this->charToFigure(color, i, j);
			if (color == WHITE)
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
		delete dstFigure; 
		this->_figuresArr[dstRow][dstCol] = srcFigure;
		this->_figuresArr[srcRow][srcCol] = nullptr;
		this->_whiteOrBlack = !this->_whiteOrBlack;
		if (typeid(*(srcFigure)).name() == "King")
		{
			this->setKingLocation(dstRow, dstCol, this->_whiteOrBlack);
		}
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

bool Board::isShah(const bool blackOrWhite)
{
	std::vector<int> figures;
	int i, size, kingRow, kingCol, row, col;
	if (blackOrWhite == WHITE)
	{
		figures = this->_whiteFigures;
		kingRow = this->_whiteKingRow;
		kingCol = this->_whiteKingCol;
	}
	else
	{
		figures = this->_blackFigures;
		kingRow = this->_blackKingRow;
		kingCol = this->_blackKingCol;
	}
	size = figures.size();
	for (int i = 0; i < size / 2; i += 2)
	{
		row = figures[i];
		col = figures[i + 1];
		if (this->_figuresArr[row][col] != nullptr)
		{

		}
	}

	return true;
}



Figure* Board::charToFigure(char f, const int& row, const int& col) const
{
	Figure* newFigure = nullptr;
	switch (tolower(f))
	{
	case KING:
		if (isupper(f))
		{
			newFigure = new King(row, col, BLACK, this);
			break;
		}
		newFigure = new King(row, col, WHITE, this);
		break;

	case QUEEN:
		if (isupper(f))
		{
			newFigure = new Queen(row, col, BLACK, this);
			break;
		}
		newFigure = new Queen(row, col, WHITE, this);
		break;

	case BISHOP:
		if (isupper(f))
		{
			newFigure = new Bishop(row, col, BLACK, this);
			break;
		}
		newFigure = new Bishop(row, col, WHITE, this);
		break;

	case ROOK:
		if (isupper(f))
		{
			newFigure = new Rook(row, col, BLACK, this);
			break;
		}
		newFigure = new Rook(row, col, WHITE, this);
		break;

	case PAWN:
		if (isupper(f))
		{
			newFigure = new Pawn(row, col, BLACK, this);
			break;
		}
		newFigure = new Pawn(row, col, WHITE, this);
		break;

	case KNIGHT:
		if (isupper(f))
		{
			newFigure = new Kinght(row, col, BLACK, this);
			break;
		}
		newFigure = new Kinght(row, col, WHITE, this);
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

