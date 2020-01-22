/** @brief Knight class used to make knight pieces
 *         
 *
 *  @details Knight class that makes knight objects and determines if its moves are valid. Checks that the knight is moving to a valid square in an L shape.
 * @authors Trystan Lee
 */

#include "Knight.h"

Knight::Knight(bool team) : ChessPiece(team, 'n') {

}
/** @brief Validmove method used to determine if a move given to a knight is valid
 *         
 *
 *  @details Valid move is a method that determines if a move is valid given a start and end square. Using the start and end square it takes its integer position
 * 	values and subtracts them. If the subtraction of the two squares multiplied by 2 is true the knight move is valid
 *	@param start,end Objects that hold the x and y coordinate of each square
 *  @return A true or false is returned if the move is valid
 *
 */
bool Knight::validMove(Square* start, Square* end) {
    int startX = start->getX();
    int startY = start->getY();
    int endX = end->getX();
    int endY = end->getY();
    int x = abs(start->getX() - end->getX());
    int y = abs(start->getY() - end->getY());
    return x * y == 2;
}
