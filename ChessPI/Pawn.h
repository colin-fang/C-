//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_PAWN_H
#define UNTITLED2_PAWN_H

#include "ChessPiece.h"
#include "Square.h"

#include <cstdlib>

class Pawn: virtual public ChessPiece {
private:

public:

    Pawn(bool team);
    bool validMove(Square* start, Square* end);


};


#endif //UNTITLED2_PAWN_H
