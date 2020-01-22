//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_BOARD_H
#define UNTITLED2_BOARD_H
#include "Square.h"
#include <cstdlib>

#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Square.h"
#include "math.h"
#include "tuple"


class Board {
private:
    bool lineCheck(Square *start, Square *end);
    void checkValidMoves(Square * square);
    void boardIni();
    Square* tiles[8][8];

public:

    Board();
    Square * findKing(bool team);
    Square* getTile(int posX, int posY);
    bool move(int startX, int startY, int endX, int endY);
    std::tuple<int,int> * getValidMoves(Square * square);
    void stateCopy(Board * duplicate);
    bool check(bool team);
    bool checkmate(bool team);
    void reset();
    void testCheckmate(bool team);

};


#endif //UNTITLED2_BOARD_H
