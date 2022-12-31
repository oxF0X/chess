#pragma once

#include <iostream>
#include <string>



class Board;

class Figure
{
public:
	Figure(const int& row, const int& col, bool color, Board* boardPtr);
	virtual ~Figure();
	virtual int isValidMove(const int& row, const int& col) = 0;
	bool getColor() const;
	std::string getLocation() const;
	void setLocation(const int& row, const int& col);
	int getCol() const;
	int getRow() const;
	char getType() const;

protected:
	char _type;
	bool _color;
	int _row;
	int _col;
	Board* _boardPtr;
};