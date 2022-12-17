#include "Figure.h"



Figure::Figure(std::string location, bool color)
{
	this->_location = location;
	this->_color = color;
}

Figure::~Figure()
{
	return;
}

void Figure::setLocation(const std::string& newLocation)
{
}

bool Figure::getColor() const
{
	return this->_color;
}

std::string Figure::getLocation() const
{
	return std::string();
}
