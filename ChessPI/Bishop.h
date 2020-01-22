//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_BISHOP_H
#define UNTITLED2_BISHOP_H


#include "ChessPiece.h"
#include "Square.h"
#include <cstdlib>

class Bishop: virtual public ChessPiece {
public:
    Bishop(bool team);
    bool validMove(Square* start, Square* end);

};


#endif //UNTITLED2_BISHOP_H
