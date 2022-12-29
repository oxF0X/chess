#include "Figure.h"
class Board;


Figure::Figure(const int& row, const int& col, bool color,  Board* boardPtr)
{
	this->_boardPtr = boardPtr;
	this->_row = row;
	this->_col = col;
	this->_color = color;
}

Figure::~Figure()
{
	return;
}


bool Figure::getColor() const
{
	return this->_color;
}

std::string Figure::getLocation() const
{
	return std::string();
}

void Figure::setLocation(const int& row, const int& col)
{
	this->_row = row;
	this->_col = col;
}
