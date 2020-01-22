/** @brief Pawn class used to make pawn objects
 *         
 *
 *  @details Pawn class that creates pawn objects and determines if its moves are valid. Checks that the pawn is either only moving 1 tile or moving 2 tiles if it hasn't moved yet.
 * @authors Geoff Vissers
 */
#include "Pawn.h"
Pawn::Pawn(bool team) : ChessPiece(team, 'p') {

}

/** @brief Validmove method used to determine if a move given to a pawn is valid
 *         
 *
 *  @details Valid move is a method that determines if a move is valid given a start and end square. Using the start and end square it takes its integer position
 * 	values and subtracts them. Makes sure that the x value doesn't change since pawns can't move left or right. it checks that the y value only changes by 1 or -1 depending on the team or
 *	the value changes by -2 if the piece hasn't moved yet
 *	@param start,end Objects that hold the x and y coordinate of each square
 *  @return A true or false is returned if the move is valid
 *
 */
bool Pawn::validMove(Square* start, Square* end) {
    int startX = start->getX();
    int startY = start->getY();
    int endX = end->getX();
    int endY = end->getY();
    if (startX - endX == 0) { //straight movement, no attack
        if (end->getPiece() != nullptr) {
            return false;
        }
        if (getTeam()) {
            if (startY - endY == -1 || (!getMoved() && abs(startY - endY) == 2)) {
                return true;
            }
        }
        else {
            if (startY - endY == 1 || (!getMoved() && abs(startY - endY) == 2)) {
                return true;
            }
        }
    }
    if (abs(startX - endX) == 1) { // diagonal move, attack
        if (end->getPiece() == nullptr || end->getPiece()->getTeam() ==
                                          getTeam()) { //if destination is empty or a member of the same team cant attack
            return false;
        }
        if (getTeam()) {
            if (startY - endY == -1) {
                return true;
            }
        }
        else {
            if (startY - endY == 1) {
                return true;
            }
        }


    }

    return false;
}



