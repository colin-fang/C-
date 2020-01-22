/** @brief King class used to create king objects of type chessPiece.
 *         
 *
 *  @details King class that makes king pieces and determines if its moves are valid. Checks that the king is only moving one tile in each direction or 1 tile in both directions(diagonal)
 * @authors Dan Le
 */

#include "King.h"

King::King(bool team) : ChessPiece(team,'k') {

}
/** @brief Validmove method used to determine if a move given to a king is valid
 *         
 *
 *  @details Valid move is a method that determines if a move is valid given a start and end square. Using the start and end square it takes its integer position
 * 	values and subtracts them. If the abs value is 1 for either the x or y it is moving 1 tile in that direction and returns true. Or if both values are 1 it returns true since it is 
 *	moving diagonally.
 *	@param start,end Objects that hold the x and y coordinate of each square
 *  @return A true or false is returned if the move is valid
 *
 */
bool King::validMove(Square* start, Square* end) {
    int startX = start->getX();
    int startY = start->getY();
    int endX = end->getX();
    int endY = end->getY();
    if((abs(startX-endX) == 1) && ((startY-endY) == 0)){
        return true;
    }
    if((abs(startY-endY) == 1) && ((startX-endX) == 0)){
        return true;
    }
    if((abs(startX-endX) == 1) && (abs(startY-endY) == 1)){
        return true;
    }
    return false;
}
