//
// Created by gviss on 2019-11-26.
//

#ifndef TEAM11_AI_H
#define TEAM11_AI_H

#include <iostream>
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Square.h"
#include "math.h"
#include "tuple"
#include <vector>
#include <algorithm>
class AI {
private:
    int minimax(int depth, Board *board, int alpha, int beta, bool color);

    int evaluateBoard(Board *board);

    int getPieceValue(ChessPiece *piece, int x, int y);

public:
    AI();
    std::tuple<int, int, int, int> minimaxRoot(int depth, Board *board, bool color);



};

#endif //TEAM11_AI_H
