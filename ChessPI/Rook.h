//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_ROOK_H
#define UNTITLED2_ROOK_H


#include "ChessPiece.h"
#include "Square.h"
#include "math.h"
class Rook: virtual public ChessPiece {
public:
    Rook(bool team);
    bool validMove(Square* start, Square* end);

};


#endif //UNTITLED2_ROOK_H
