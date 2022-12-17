#pragma once
#include "Knight.h"
#include "Figure.h"

class Kinght : public Figure
{
public:
	Kinght(std::string location, bool isWhite);
	virtual ~Kinght();
};