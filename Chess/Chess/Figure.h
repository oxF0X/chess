#pragma once

#include <iostream>
#include <string>


class Figure
{
public:
	Figure(std::string location, bool color);
	~Figure();
	virtual int isValidMove(const std::string& move) = 0;
	virtual bool canEat(const std::string& move) = 0;
	void setLocation(const std::string& newLocation);
	bool getColor() const;
	std::string getLocation() const;

protected:
	bool _color;
	std::string _location;

};