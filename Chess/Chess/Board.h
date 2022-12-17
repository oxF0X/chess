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
#define SIZE 8 
#define DEFAULT_MAP "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr1"
#define INVALID_MOVE 0
#define VALID_MOVE_SHAH_ON_OPPONENT 2
#define TEAM_FIGURE_ON_DST_LOCATION 3
#define MOVE_WILL_CAUSE_SHAH_ON_THE_TEAM 4
#define	ILLEGAL_MOVE 6	
#define	CHECKMATE 8
#define KING 'k'
#define QUEEN 'q'
#define ROOK 'r'
#define KNIGHT 'n'
#define PAWN 'p'
#define EMPTY_LOCATION '#'


/*
לאתחל את הלוח
בנאי שמקבל את המחרוזת של הלוח ומסדר את הלוח אם לולאה
ויהיה דם בנאי דיפולטיבי שימיין לפי סדר דיפולטיבי.
 נקרא לפונקציה GETFIGURE
שהיא תעשה:
תבדוק שבמקור יש  כלי
תבדוק אם הכלי הוא הכלי של הצבע המתאים
לבדוק אם ביעד יש כלי או לא
בהתאם לבדיקה לקורא לפונקציות הבדיקה של הכלים עצמם
להזיז את הכלי עצמו ולשמור עותק
בודקים האם נגרם שח לעצמינו אם כן להחזיר למצב הקודם
אם לא לבוק האם נגרם שח ליריב
*/
class Board
{
public:
	Board(std::string toolsMap = DEFAULT_MAP);
	int move(std::string location);

private:
	Figure* getFigure(std::string location) const;
	bool isShah();
	Figure* getTools() const;
	Figure* charToFigure(char f, std::string location) const;

	Figure* _figuresArr[SIZE][SIZE];
	bool _isWhiteOrBlack;
	std::string _whiteKingLocation;
	std::string _blackKingLocation;
	static int _numOfBoards;
};