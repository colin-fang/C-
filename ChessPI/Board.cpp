/** @brief Board class for representing the physical board
 *         
 *
 *  @details Consists of a 8x8 array of Square objects, to represent indivual spots on the board. Each tile can hold a ChessPiece.
 * The board class also contains various methods for moving pieces, checking for/creating end-game conditions, accessing piece-specific functions, creating a copy of the board, and resetting the board to it's initial state.
 *
 * @authors Geoffrey Vissers
 */

#include "Board.h"


/** @brief Constructor for the board
 *         
 *  @details Calls the boardIni() to create a fresh board
 */

Board::Board() {
    boardIni();

}

/** @brief getTile() to access a square at given position
 *         
 *  @details returns the Square at a given position
 *  @param posX, posY integers that represent the tile on the board
 *  @return pointer to the Square at posX,posY
 */
Square* Board::getTile(int posX, int posY) {
    return tiles[posX][posY];
}

/** @brief Initializer for the board
 *         
 *  @details sets the board to the starting position with pieces in proper place
 * 
 */

void Board::boardIni() {
    for (int i = 0; i < 8; i++) { //clears all pieces from the board
        for (int j = 0; j < 8; j++)
            tiles[i][j] = new Square(i, j, nullptr);

    }
    for(int i = 0; i < 8; i ++){ //sets up the pawns
        tiles[i][1]->setPiece(new Pawn(true));
        tiles[i][6]->setPiece(new Pawn(false));
    }
  	//sets the rest of the pieces
    tiles[0][0]->setPiece(new Rook(true));
    tiles[7][0]->setPiece(new Rook(true));
    tiles[0][7]->setPiece(new Rook(false));
    tiles[7][7]->setPiece(new Rook(false));

    tiles[1][0]->setPiece(new Knight(true));
    tiles[6][0]->setPiece(new Knight(true));
    tiles[1][7]->setPiece(new Knight(false));
    tiles[6][7]->setPiece(new Knight(false));

    tiles[2][0]->setPiece(new Bishop(true));
    tiles[5][0]->setPiece(new Bishop(true));
    tiles[2][7]->setPiece(new Bishop(false));
    tiles[5][7]->setPiece(new Bishop(false));

    tiles[3][0]->setPiece(new Queen(true));
    tiles[4][0]->setPiece(new King(true));
    tiles[3][7]->setPiece(new Queen(false));
    tiles[4][7]->setPiece(new King(false));



}


/** @brief move function for moving pieces around the board
 *         
 *  @details Takes in a starting and end position, and uses each piece's rules to determine if it is valid, adn ensure that the move doesnt result in a check
 *  @param startX,startY,endX,endY representing the coordinates for the move
 *  @return true or false, depending on if it was a valid move
 */

bool Board::move(int startX, int startY, int endX, int endY){
    Square* startSquare = tiles[startX][startY];
    Square* endSquare = tiles[endX][endY];
    if(startSquare->getPiece() == nullptr){
        return false;
    }
    checkValidMoves(startSquare);
    bool move = false;
    for(int i = 0; i < 27; i++){ //checks that the move is in that pieces valid move list
     if(std::get<0>(startSquare->getPiece()->validMoves[i]) == endX && std::get<1>(startSquare->getPiece()->validMoves[i]) == endY){ //checks if attempted move is in the valid move array
            move = true;
            break;
     }
    }
    if(!move){ //break if false
        return false;
    }
    else{
        if((startSquare->getPiece()->getType() != 'n' && startSquare->getPiece()->getType() != 'k') && !lineCheck(startSquare, endSquare)){ //straight line check
            return false;
        }

        if(endSquare->getPiece() != nullptr){ //not empty end square
            bool mvd = startSquare->getPiece()->getMoved();
            ChessPiece *captured = endSquare->getPiece();
            endSquare->getPiece()->setCaptured(true);
            endSquare->setPiece(startSquare->getPiece());
            startSquare->getPiece()->setMoved(true);
            startSquare->setPiece(nullptr);
            if(check(endSquare->getPiece()->getTeam())){ //tries the move, if in check after resets and returns false
                startSquare->setPiece(endSquare->getPiece());
                startSquare->getPiece()->setMoved(mvd);
                endSquare->setPiece(captured);
                captured->setCaptured(false);
                return false;
            }
            return true; //returns true if move went through
        }
        else{ //same as above, but no piece occupies the end square
            bool mvd = startSquare->getPiece()->getMoved();
            endSquare->setPiece(startSquare->getPiece());
            startSquare->getPiece()->setMoved(true);
            startSquare->setPiece(nullptr);
            if(check(endSquare->getPiece()->getTeam())){
                startSquare->setPiece(endSquare->getPiece());
                startSquare->getPiece()->setMoved(mvd);
                endSquare->setPiece(nullptr);
                return false;

            }
            return true;
        }
    }
}

/** @brief checks the valid moves available for a given piece on a tile
 *         
 *  @details adds all the valid moves to that piece's move list
 *  @param square, the tile containing the piece to check
 *  
 */

void Board::checkValidMoves(Square* square){
    int x = square->getX();
    int y = square->getY();
    square->getPiece()->resetMoves(); //wipe the pieces move list
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8;j++){
            if(i == x && j == y){ //ignore its current tile
                continue;
            }
            else{
                Square* endSquare = tiles[i][j];
                bool valid = square->getPiece()->validMove(square,endSquare); //call the pieces specific validMove to see if suggested move is allowed
                if(valid){
                    if(lineCheck(square, endSquare) || (square->getPiece()->getType() == 'k' || square->getPiece()->getType() == 'n')) { //checks the straight line condition for ones that need it
                        if(!(endSquare->getPiece() != nullptr && endSquare->getPiece()->getTeam() == square->getPiece()->getTeam())){ //if destination is not empty, makes sure it is not a friendly piece
                            square->getPiece()->addMoves(i, j); //adds the move to the list of moves
                        }

                    }
                }
            }
        }
    }
}


/** @brief line check to make sure pieces do not "jump" over pieces if they arent allowed to
 *         
 *  @details checks every square in between destination and end, if its a clear path returns true, else false
 *  @param start, end, the beginning and destination for the piece to check
 *  @return true if valid move, else false
 */
bool Board::lineCheck(Square *start, Square *end) { //
    int distance;
    bool moveX;
    bool diagonal;
    int diaDirectionX;
    int distanceX;
    int distanceY;
    int diaDirectionY;
    bool valid = true;
    int startX = start->getX();
    int startY = start->getY();
    int endX = end->getX();
    int endY = end->getY(); 
    diagonal = !(startX == endX | startY == endY); //moving diagonally
    if (!diagonal) { //get vertical/horizontal distance
        if (startX == endX) {
            distance = -(startY - endY);
            moveX = true;
        } else { 
            distance = -(startX - endX);
            moveX = false;
        }
    } else { //get diagonal distances
        distanceX = startX - endX;
        distanceY = startY - endY;

        diaDirectionX = -abs(startX - endX)/distanceX;
        diaDirectionY = -abs(startY - endY)/distanceY;
    }
    if(!diagonal && abs(distance) == 1 || (diagonal && abs(distanceX) == 1)){ //if only moving 1 square always valid
        return true;
    }
    if(!diagonal){ //checks vert/horizontal
        for(int i = 1; i < abs(distance); i++){
            int j = i * abs(distance)/distance;
            if(moveX){ //checks for x staying the same

                if(tiles[startX][startY + j]->getPiece()!= nullptr){
                    valid = false;
                    break;
                }
            }
            else{ // check for y staying the same
                if(tiles[startX + j][startY]->getPiece() != nullptr){
                    valid = false;
                    break;
                }
            }
        }
    }
    else{ //checks diagonal
        for(int i = 1; i < abs(distanceX) ; i++){
            int j = i * diaDirectionX;
            int k = i * diaDirectionY;

            if(tiles[startX + j][startY + k]->getPiece() != nullptr){
                valid = false;
                break;
            }
        }
    }
    return valid;
}

/** @brief returns the valid moves for a piece on a square
 *         
 *  @details returns valid moves
 *  @param square, position on the board to check
 *  @return pointer to an array of valid moves
 */

std::tuple<int, int> *Board::getValidMoves(Square *square) {
    if(square->getPiece()!= nullptr){
        checkValidMoves(square);
        return square->getPiece()->validMoves;
    }
    return nullptr;
}


/** @brief Creates a copy of the board
 *         
 *  @details creates a new board and copies each piece in each position over
 *  @param duplicate, the board to copy into
 *
 */
void Board::stateCopy(Board * duplicate) {
    for(int i = 0; i < 8; i ++){
        for(int j = 0; j< 8; j++){
            duplicate->getTile(i,j)->setPiece(this->getTile(i,j)->getPiece());
        }
    }

}

/** @brief Checkmate returns true or false for if a team is in checkmate
 *         
 *  @details goes through every move a team can make, if none result in not being in check, it is checkmate
 *  @param team, the team to check checkmate for
 *  @return true for checkmate, false otherwise
 */
bool Board::checkmate(bool team) {
    Board *cpy = new Board(); //copy of board to allow moving and checking, then resetting
    stateCopy(cpy);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((tiles[i][j]->getPiece() == nullptr) || tiles[i][j]->getPiece()->getTeam() != team) { //ignore empty tiles and other teams pieces
                continue;
            }
            std::tuple<int, int> *moves = getValidMoves(getTile(i, j)); //create a copy of the pieces valid moves
            std::tuple<int, int> validMoves[28];
            for (int k = 0; k < 28; k++) {
                std::get<0>(validMoves[k]) = std::get<0>(*moves);
                std::get<1>(validMoves[k]) = std::get<1>(*moves);
                moves++;
            } 
            for (int l = 0; l < 28; l++) { //tries each move
                if (std::get<0>(validMoves[l]) == -1) {
                    break;
                }
                int mvx = std::get<0>(validMoves[l]);
                int mvy = std::get<1>(validMoves[l]);
                bool mvd = tiles[i][j]->getPiece()->getMoved();
                move(i, j, mvx, mvy);
                if (!check(team)) { //if move results in not being in check, restore board and return false
                    cpy->stateCopy(this);
                    tiles[i][j]->getPiece()->setMoved(mvd);
                    return false;
                }
                cpy->stateCopy(this);
                tiles[i][j]->getPiece()->setMoved(mvd);
            }
        }
    }
    return true; //if no move exists, team is in checkmate, return true
}

/** @brief findKing returns the square containing the king for a given team
 *         
 *  @details loops thru board until king is found
 *  @param team, whose king to search for
 *  @return square where the king is
 */

Square * Board::findKing(bool team){
    Square * kingLocation;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            if(tiles[i][j]->getPiece() == nullptr){
                continue;
            }
            if(tiles[i][j]->getPiece()->getType() == 'k' && tiles[i][j]->getPiece()->getTeam() == team){
                kingLocation = tiles[i][j];
                return kingLocation;
            }
        }
    }
    return nullptr;
}


/** @brief Check returns true or false for if a team is in check

 *  @details checks every pieces posssible moves, and if the king's square is in there, the other team is in check, and so true is returned
 *  @param team, the team to check check for
 *  @return true for check, false otherwise
 */

bool Board::check(bool team) {
    bool check = false;
    Square* kingLocation;
    kingLocation = findKing(team);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tiles[i][j]->getPiece() == nullptr|| tiles[i][j]->getPiece()->getTeam() == team){
                continue;
            }
            std::tuple<int,int> *moves = getValidMoves(tiles[i][j]);
            while(std::get<0>(*moves) != -1){
                if(std::get<0>(*moves) == kingLocation->getX() && std::get<1>(*moves) == kingLocation->getY()){ //found a move where king can be taken, return true as team is in check
                    check = true;
                    break;
                }
                moves++;
            }
        }
    }
    return check; 
}

/** @brief reset puts board back to initial state
 *         
 *  @details calls boardIni() to reset board
 *  
 */
void Board::reset() {
    boardIni();

}

/** @brief causes a checkmate for testing purposes
 *         
 *  @details sets up the team given in such a position to cause checkmate
 *  @param team, the team that is to win
 */
void Board::testCheckmate(bool team){
    for (int i = 0; i < 8; i++) { //clears all pieces from the board
        for (int j = 0; j < 8; j++)
            tiles[i][j] = new Square(i, j, nullptr);

    }
    tiles[0][0]->setPiece(new King(!team));
    tiles[0][2]->setPiece(new Queen(team));
    tiles[1][2]->setPiece(new Queen(team));
}




