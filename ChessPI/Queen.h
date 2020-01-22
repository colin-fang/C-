//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_QUEEN_H
#define UNTITLED2_QUEEN_H

#include "ChessPiece.h"
#include "Square.h"
#include <cstdlib>

class Queen: virtual public ChessPiece {
public:
    Queen(bool team);
    bool validMove(Square* start, Square* end);

};

#endif //UNTITLED2_QUEEN_H
