#include "MathUtils.h"

std::string MathUtils::intLocationToStr(int col, int row)
{
    std::string location = "";
    location += (char)(row + A_ASCII_CODE);
    location += (char)(col + ONE_ASCII_CODE);
    return location;
}

int* MathUtils::strLocationToInt(std::string location)
{
    int* arr = new int[2];
    arr[COL] = ((int)(location[1])) - A_ASCII_CODE;
    std::cout << arr[COL];
    arr[ROW] = ((int)(location[0])) - ONE_ASCII_CODE;
    std::cout << arr[ROW];
    return arr;
}
