#pragma once

#include <iostream>
#include <string>


class Figure
{
public:
	Figure(std::string location, bool isWhite);
	~Figure();
	virtual int isValidMove(const std::string& move) = 0;
	virtual bool canEat(const std::string& move) = 0;
	void setLocation(const std::string& newLocation);
	bool isWhiteColor() const;
	std::string getLocation() const;

protected:
	bool _isWhite;
	std::string _location;

};