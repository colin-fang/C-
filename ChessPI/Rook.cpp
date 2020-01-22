/** @brief Rook class used to make rook pieces.
 *         
 *
 *  @details Rook class that makes rook pieces and determines if its moves are valid. Checks that the rook is only moving in one direction either in the x or y plane.
 * @authors Dan Le
 */
#include "Rook.h"

Rook::Rook(bool team) : ChessPiece(team,'r') {

}
/** @brief Validmove method used to determine if a move given to a rook is valid
 *         
 *
 *  @details Valid move is a method that determines if a move is valid given a start and end square. Checks if both x square values are the same or if both y square values are the same
 *	if the x or y values are the same it's moving in the x or y plane which makes it a valid move
 *	@param start,end Objects that hold the x and y coordinate of each square
 *  @return A true or false is returned if the move is valid
 *
 */
bool Rook::validMove(Square* start, Square* end) { 
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
    return false;


}
