#pragma once

#include <iostream>
#include <string>
//#include "Board.h"


class Board;

class Figure
{
public:
	Figure(std::string location, bool color, const Board* boardPtr);
	virtual ~Figure();
	virtual int isValidMove(const std::string& move) = 0;
	bool getColor() const;
	std::string getLocation() const;
	void setLocation(std::string& location);

protected:
	bool _color;
	std::string _location;
	const Board* _boardPtr;
};