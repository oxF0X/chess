#include "Figure.h"

Figure::Figure(std::string location, bool isWhite)
{
	this->_location = location;
	this->_isWhite = isWhite;
}

Figure::~Figure()
{
	return;
}
