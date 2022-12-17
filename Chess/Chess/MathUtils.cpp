#include "MathUtils.h"

std::string MathUtils::intLocationToStr(int col, int row)
{
    std::string location = "";
    location += (char)(row + A_ASCII_CODE);
    location += (char)(col + 1);
    return location;
}
