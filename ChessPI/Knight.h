//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_KNIGHT_H
#define UNTITLED2_KNIGHT_H


#include "ChessPiece.h"
#include "Square.h"
#include <cstdlib>

class Knight: virtual public ChessPiece {
public:
    Knight(bool team);
    bool validMove(Square* start, Square* end);

};
#endif //UNTITLED2_KNIGHT_H
