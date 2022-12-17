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

void Figure::setLocation(const std::string& newLocation)
{
}

bool Figure::isWhiteColor() const
{
	return false;
}

std::string Figure::getLocation() const
{
	return std::string();
}
