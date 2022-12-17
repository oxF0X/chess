#include "Board.h"

int Board::_numOfBoards = 0;

Board::Board(std::string toolsMap)
{
	if (this->_numOfBoards)
	{
		throw(std::string("Too many boards"));
	}
	this->_numOfBoards++;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			 this->_figuresArr[i][j] = this->charToFigure(toolsMap[i * SIZE + j], MathUtils::intLocationToStr(j, i));
		}
	}

}

int Board::move(std::string location)
{
	Figure* srcFigure = nullptr;
	Figure* dstFigure = nullptr;
	std::string src = location.substr(location.length() / 2);
	std::string dst = location.substr(location.length() / 2, location.length());
	srcFigure = this->getFigure(src);
	if (srcFigure == nullptr)
	{
		return;
	}
}

Figure* Board::getFigure(std::string location) const
{
	Figure* newFigure = nullptr;
	int row = (int)(location[0]) - A_ASCII_CODE;
	int col = (int)(location[1]) --;
	
	if (this->_figuresArr[row, col] == nullptr || (*this->_figuresArr[row, col])->getColor() == this->_isWhiteOrBlack)
	{
		return newFigure;
	}
	return (*this->_figuresArr[row, col]);
}

bool Board::isShah()
{
	return false;
}

Figure* Board::getTools() const
{
	return nullptr;
}


Figure* Board::charToFigure(char f, std::string location) const
{
	Figure* newFigure = nullptr;
	switch (tolower(f))
	{
	case KING:
		if (isupper(f))
		{
			newFigure = new King(location, BLACK);
			break;
		}
		newFigure = new King(location, WHITE);
		break;

	case QUEEN:
		if (isupper(f))
		{
			newFigure = new Queen(location, BLACK);
			break;
		}
		newFigure = new Queen(location, WHITE);
		break;

	case BISHOP:
		if (isupper(f))
		{
			newFigure = new Bishop(location, BLACK);
			break;
		}
		newFigure = new Bishop(location, WHITE);
		break;

	case ROOK:
		if (isupper(f))
		{
			newFigure = new Rook(location, BLACK);
			break;
		}
		newFigure = new Rook(location, WHITE);
		break;

	case PAWN:
		if (isupper(f))
		{
			newFigure = new Pawn(location, BLACK);
			break;
		}
		newFigure = new Pawn(location, WHITE);
		break;

	case KNIGHT:
		if (isupper(f))
		{
			newFigure = new Kinght(location, BLACK);
			break;
		}
		newFigure = new Kinght(location, WHITE);
		break;

	default:
		break;

	}
	return newFigure;
}



