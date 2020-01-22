//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_SQUARE_H
#define UNTITLED2_SQUARE_H


#include "ChessPiece.h"
class ChessPiece;
class Square {

private:
    ChessPiece* piece;
    int posX;
    int posY;

public:
    Square(int, int, ChessPiece*);
    ChessPiece* getPiece();
    void setPiece(ChessPiece* p);
    void setX( int x);
    void setY(int y);
    int getX();
    int getY();





};


#endif //UNTITLED2_SQUARE_H
