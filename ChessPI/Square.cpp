/** @brief Square class for the board
 *         
 *
 *  @details Square class that holds the x position,y position and type of piece on the square
 * @authors Geoff Vissers
 */
#include "Square.h"

/** @brief Square constructor
 *         
 *
 *  @details Square constructor that saves the x and y coordinates and saves the type of piece on it
 *	@param x,y x and y are coordinates of the square
 *	@param piece The type of piece that is currently on the square
 */
Square::Square(int x, int y, ChessPiece* piece) {
    this->posX = x;
    this->posY = y;
    this->piece = piece;
}
/** @brief getPiece- gets the piece on the square
 *         
 *
 *  @details returns the piece that is on the square could be any peice type
 *	@return piece- the piece that is on the square
 */
ChessPiece* Square::getPiece() {
    return this->piece;
}
/** @brief setPiece- gets the piece on the square
 *         
 *
 *  @details sets the piece that is on the square changes the saved piece variable
 *	@param p- the piece that is now on the square
 */
void Square::setPiece(ChessPiece* p) {
    this->piece = p;

}
/** @brief setX- sets the x position of the square
 *         
 *
 *  @details sets the square's x position
 *	@param p- the x position
 */
void Square::setX(int x) {
    this->posX = x;
}
/** @brief setY- sets the y position of the square
 *         
 *
 *  @details sets the square's y position
 *	@param  the y position
void Square::setY(int y) {
    this->posY = y;
}
/** @brief getX- gets the x value of the square
 *         
 *
 *  @details returns x positional value of the square that is held in the square
 *	@return posX the x position
 */
int Square::getX() {
    return posX;
}
/** @brief getY- gets the y value of the square
 *         
 *
 *  @details returns y positional value of the square that is held in the square
 *	@return posY the y position
 */
int Square::getY() {
    return posY;
}
