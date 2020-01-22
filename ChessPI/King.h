//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_KING_H
#define UNTITLED2_KING_H


#include "ChessPiece.h"
#include "Square.h"
#include <cstdlib>

class King: virtual public ChessPiece {
public:
    King(bool team);
    bool validMove(Square* start, Square* end);

};


#endif //UNTITLED2_KING_H
