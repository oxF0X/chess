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
			 this->_figuresArr[i][j] = this->charToFigure(toolsMap[i * SIZE + j], i * SIZE + j);
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
		return
	}
}

Figure* Board::getFigure(std::string location) const
{
	if()
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
			newFigure = new King(location, BLACK)
		}
	}
}



