#pragma once

#include <vector>
#include <string>
#include "Figure.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "MathUtils.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Pipe.h"


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


class Board
{
	friend class King;
	friend class Pawn;
public:
	static Board getBoard(Pipe* p, std::string toolsMap = DEFAULT_MAP);
	int move(std::string location);
	bool isEmpty(int row, int col) const;
	void setKingLocation(const int& row, const int& col, bool color);
	virtual ~Board();

private:
	std::string createBoardMap() const;
	Board(Pipe* p, std::string toolsMap);
	Figure* getSrcFigure(int& row, int& col) const;
	int checkDst(int& row, int& col) const;
	bool isShah(const bool blackOrWhite, int row, int col);
	Figure* charToFigure(char f, const int& row, const int& col);
	bool isCheckmate(const bool color);

	//std::vector<int> _blackFigures;
	//std::vector<int> _whiteFigures;
	std::vector<Figure*> _attackingFigures;
	Figure* _figuresArr[SIZE][SIZE];
	bool _whiteOrBlack;
	bool _isCastling;
	int _whiteKingCol;
	int _whiteKingRow;
	int _blackKingCol;
	int _blackKingRow;
	int _castlingSrcRow;
	int _castlingSrcCol;
	int _castlingDstRow;
	int _castlingDstCol;
	static int _numOfBoards;
	Pipe* _p;
	
};