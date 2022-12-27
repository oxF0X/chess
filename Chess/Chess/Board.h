#pragma once

#include <string>
#include "Figure.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "MathUtils.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"


#define WHITE false
#define BLACK true
#define COLOR_INDEX 65
#define SIZE 8 
#define DEFAULT_MAP "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr1"
#define VALID_MOVE 0
#define VALID_MOVE_SHAH_ON_OPPONENT 1
#define INVALID_SRC_FIGURE 2
#define TEAM_FIGURE_ON_DST_LOCATION 3
#define MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM 4
#define	ILLEGAL_MOVE 6	
#define	CHECKMATE 8
#define KING 'k'
#define QUEEN 'q'
#define ROOK 'r'
#define KNIGHT 'n'
#define PAWN 'p'
#define BISHOP 'b'
#define EMPTY_LOCATION '#'

//class Rook;
//class Bishop;
//class King;
//class Knight;
//class Pawn;
//class Queen;
//class Figure;

class Board
{
public:
	static Board getBoard(std::string toolsMap = DEFAULT_MAP);
	int move(std::string location);
	bool isEmpty(int row, int col) const;

private:
	Board(std::string toolsMap);
	Figure* getSrcFigure(int& row, int& col) const;
	int checkDst(int& row, int& col) const;
	bool isShah();
	Figure* charToFigure(char f, const int& row, const int& col) const;

	Figure* _figuresArr[SIZE][SIZE];
	bool _whiteOrBlack;
	std::string _whiteKingLocation;
	std::string _blackKingLocation;
	static int _numOfBoards;
};