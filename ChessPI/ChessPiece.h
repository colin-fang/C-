//
// Created by Geoff on 2019-10-29.
//

#ifndef UNTITLED2_CHESSPIECE_H
#define UNTITLED2_CHESSPIECE_H

#include "Square.h"
#include "tuple"


class Square;

class ChessPiece {
private:
    bool captured = false;
    bool white = false;
    bool moved;
    char type;
    int moveCount;
    

public:
    char getType();
    std::tuple<int,int> validMoves[27];
    void resetMoves();
    void addMoves(int x, int y);
    ChessPiece();
    ChessPiece(bool team, char type);
    bool getTeam();
    void setTeam(bool team);
    bool isCaptured();
    void setCaptured(bool capture);
    virtual bool validMove(Square* start, Square* end);
    bool getMoved();
    void setMoved(bool move);
    void clearMoves();
};



#endif //UNTITLED2_CHESSPIECE_H
