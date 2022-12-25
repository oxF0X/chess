#include "Figure.h"
class Board;


Figure::Figure(std::string location, bool color, const Board* boardPtr) : _boardPtr(boardPtr)
{
	this->_location = location;
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

void Figure::setLocation(std::string& location)
{
	this->_location = location;
}
