/** @brief Chesspiece class used to create chess piece objects.
 *         
 *
 *  @details Chesspiece function that is the parent of all other pieces. It saves the type of piece and which team the piece is on.
 * @authors Geoff Vissers
 */
#include "ChessPiece.h"
/** @brief Chess piece constructor
 *         
 *
 *  @details Chess piece constructor 
 *	@param team- a boolean that saves which team the piece is on
 *	@param type What type of piece the chess piece is
 */
ChessPiece::ChessPiece(bool team, char type) {
    this->type = type;
    this->white = team;
    this->captured = false;

    resetMoves();


}
/** @brief getTeam- gets the team of the piece
 *         
 *
 *  @details returns the team of the piece either black or white
 *	@return the team that the piece is on
 */
bool ChessPiece::getTeam() {
    return this->white;
}
/** @brief sets the team of the piece
 *         
 *
 *  @details sets the team of the piece either to white or black
 *	@param  the team the piece is being changed to
 */
void ChessPiece::setTeam(bool team) {
    this->white = team;
}
/** @brief returns if the piece is captured
 *         
 *
 *  @details returns if the piece is captured
 *	@return  if the piece is captured
 */
bool ChessPiece::isCaptured() {
    return this->captured;
}
/** @brief sets the piece to being captured
 *         
 *
 *  @details sets the piece to being captured
 *	@param the boolean referring to if the piece is captured or not
 */
void ChessPiece::setCaptured(bool capture) {
    this->captured = capture;

}
/** @brief checks if the move is valid
 *         
 *
 *  @details checks if the move is valid but it uses the child function so this function is just a placeholder
 *	@return true if its a valid move or false if it isn't
 */
bool ChessPiece::validMove(Square* start, Square* end) {
    return false;
}
/** @brief returns if the piece has moved 
 *         
 *
 *  @details returns if the piece has moved this is used for pawns
 *	@return true or false if the piece has moved or not
 */
bool ChessPiece::getMoved(){
    return this->moved;
}
/** @brief default constructor if no parameters are given
 *         
 *
 *  @details constructor called when no parameters are given
 */
ChessPiece::ChessPiece() {
    this->white = false;
    this->captured = false;
}
/** @brief sets the moved value to true
 *         
 *
 *  @details used when the piece moves called when a piece first moves.
 *	@param  a boolean containing true or false(probably true) since the piece moved
 */
void ChessPiece::setMoved(bool move) {
    this->moved = move;

}

/** @brief Adds valid moves to an array
 *         
 *
 *  @details Adds valid moves to the array for the piece to be used
 *	@param x,y the positions of the piece
 */
void ChessPiece::addMoves(int x, int y) {
   std::get<0>(this->validMoves[moveCount]) = x;
    std::get<1>(this->validMoves[moveCount]) = y;
   moveCount ++;
}

/** @brief clears the current valid moves
 *
 *  @details sets the current valid moves all to -1 making them cleared
 */
void ChessPiece::resetMoves() {
    for (int i = 0; i < 27; i++) { //intialize move array
        std::get<0>(this->validMoves[i]) = -1;
        std::get<1>(this->validMoves[i]) = -1;
    }
    this->moveCount = 0;
}
/** @brief gets the type of piece
 *         
 *
 *  @details gets the saved type of piece in the object
 *	@return  the type of piece
 */
char ChessPiece::getType() {
    return type;
}
