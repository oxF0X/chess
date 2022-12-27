#include "Board.h"

class Board;
int Board::_numOfBoards = 0;


// CTOR
Board::Board(std::string toolsMap)
{
	this->_whiteOrBlack = (int)toolsMap[COLOR_INDEX];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{	
			char l = toolsMap[(i * SIZE + abs(j - SIZE + 1))];
			this->_figuresArr[i][j] = this->charToFigure(toolsMap[i * SIZE + abs(j - SIZE + 1)], abs(SIZE - j - 1),abs(SIZE - i - 1));
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

bool Board::isShah()
{
	return false;
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

