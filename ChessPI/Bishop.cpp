/** @brief Bishop class used to create bishop objects.
 *         
 *
 *  @details Bishop class used to create bishops and determine valid moves using the valid move function. 
 *  Takes the squares given to it and takes the absolute values of each coordinate and determines if it's valid
 * @authors Dan Le
 */

#include "Bishop.h"

Bishop::Bishop(bool team) : ChessPiece(team,'b') {

}
/** @brief Validmove method used to determine if a move given to a bishop is valid
 *         
 *
 *  @details Valid move is a method that determines if a move is valid given a start and end square. It takes the starting x and starting y and ending x and ending y and puts them all 
 * into variables that are then subtracted to check if their absolute values are equal. If their absolute values are equal when subtracting it means its moved diagonally which means the move is valid.
 * 	@param start,end Objects that hold the x and y coordinate of each square
 *  @return A true or false is returned if the move is valid
 */
bool Bishop::validMove(Square* start, Square* end) {
    int startX = start->getX();
    int startY = start->getY();
    int endX = end->getX();
    int endY = end->getY();
    if(abs(startX-endX) == abs(startY-endY)){
        return true;
    }else{
        return false;
    }
}
