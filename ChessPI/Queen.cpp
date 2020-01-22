/** @brief Queen class used to make queen pieces.
 *         
 *
 * @details Queen class that creates queen objects and determines if its moves are valid. Checks that the queen is only doing moves that are valid rook moves or valid bishop moves
 * @authors Dan Le
 */
#include "Queen.h"

Queen::Queen(bool team) : ChessPiece(team,'q') {

}

/** @brief Validmove method used to determine if a move given to a Queen is valid
 *         
 *
 *  @details Valid move is a method that determines if a move is valid given a start and end square. Using the start and end square it takes its integer position
 * 	values and subtracts them. If the start and end squares do a valid bishop move where the absolute value of the positions subtracted are equal then returns true.
 *	checks if the x position values are equal or the y values are equal which means its doing a valid rook move which also would return true.
 *	@param start,end Objects that hold the x and y coordinate of each square
 *  @return A true or false is returned if the move is valid
 *
 */
bool Queen::validMove(Square* start, Square* end) {
    int startX = start->getX();
    int startY = start->getY();
    int endX = end->getX();
    int endY = end->getY();
    if(startX == endX) {
        return true;
    }
    if(startY == endY){
        return true;
    }
    if(abs(startX-endX) == abs(startY-endY)){
        return true;
    }
    return false;

}
