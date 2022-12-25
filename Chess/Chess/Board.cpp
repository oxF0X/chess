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
			this->_figuresArr[i][j] = this->charToFigure(toolsMap[(i * SIZE + abs(j - SIZE + 1))], MathUtils::intLocationToStr(abs(SIZE-j), abs(SIZE - i)));
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
	std::string src = location.substr(0, location.length() / 2);
	std::string dst = location.substr(location.length() / 2);
	srcFigure = this->getSrcFigure(src);
	if (srcFigure == nullptr)
	{
		return INVALID_SRC_FIGURE;
	}
	if (this->checkDst(dst) == TEAM_FIGURE_ON_DST_LOCATION)
	{
		return TEAM_FIGURE_ON_DST_LOCATION;
	}
	code = srcFigure->isValidMove(dst);
	if (code == VALID_MOVE)
	{
		int* dstLocation = MathUtils::strLocationToInt(dst);
		int* srcLocation = MathUtils::strLocationToInt(src);
		dstFigure = this->_figuresArr[dstLocation[ROW]][dstLocation[COL]];
		delete dstFigure;
		this->_figuresArr[dstLocation[ROW]][dstLocation[COL]] = srcFigure;
		this->_figuresArr[srcLocation[ROW]][srcLocation[COL]] = nullptr;
		this->_whiteOrBlack = !this->_whiteOrBlack;
		delete[] dstLocation;
		delete[] srcLocation;
	}
	std::cout << "The code is: " << code << std::endl;
	return code;

}


Figure* Board::getSrcFigure(std::string location) const
{
	Figure* newFigure = nullptr;
	int* locationArr = MathUtils::strLocationToInt(location);
	if (this->isEmpty(locationArr[ROW], locationArr[COL]) || (this->_figuresArr[locationArr[ROW]][locationArr[COL]])->getColor() != this->_whiteOrBlack)
	{
		return newFigure;
	}
	return (*this->_figuresArr[locationArr[ROW], locationArr[COL]]);
}

int Board::checkDst(std::string location) const
{
	Figure* newFigure = nullptr;
	int* locationArr = MathUtils::strLocationToInt(location);
	bool x = this->isEmpty(locationArr[ROW], locationArr[COL]);
	if (this->isEmpty(locationArr[ROW],locationArr[COL]) || this->_figuresArr[locationArr[ROW]][locationArr[COL]]->getColor() != this->_whiteOrBlack)
	{
		return VALID_MOVE;
	}
	return TEAM_FIGURE_ON_DST_LOCATION;
}

bool Board::isShah()
{
	return false;
}



Figure* Board::charToFigure(char f, std::string location) const
{
	Figure* newFigure = nullptr;
	switch (tolower(f))
	{
	case KING:
		if (isupper(f))
		{
			newFigure = new King(location, BLACK, this);
			break;
		}
		newFigure = new King(location, WHITE, this);
		break;

	case QUEEN:
		if (isupper(f))
		{
			newFigure = new Queen(location, BLACK, this);
			break;
		}
		newFigure = new Queen(location, WHITE, this);
		break;

	case BISHOP:
		if (isupper(f))
		{
			newFigure = new Bishop(location, BLACK, this);
			break;
		}
		newFigure = new Bishop(location, WHITE, this);
		break;

	case ROOK:
		if (isupper(f))
		{
			newFigure = new Rook(location, BLACK, this);
			break;
		}
		newFigure = new Rook(location, WHITE, this);
		break;

	case PAWN:
		if (isupper(f))
		{
			newFigure = new Pawn(location, BLACK, this);
			break;
		}
		newFigure = new Pawn(location, WHITE, this);
		break;

	case KNIGHT:
		if (isupper(f))
		{
			newFigure = new Kinght(location, BLACK, this);
			break;
		}
		newFigure = new Kinght(location, WHITE, this);
		break;

	default:
		break;

	}
	return newFigure;
}

bool Board::isEmpty(int col, int row) const
{
	return this->_figuresArr[row][col] == nullptr;
}

