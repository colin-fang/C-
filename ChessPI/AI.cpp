/**@brief A Class that calculates the best possible valid move for the computer player
*
*@details A Class that implements Minimax and Alpha Beta pruning.
*Uses chess piece values by type and 8x8 matricies of positional evaluation scoring
*to calculate the best valid move the computer player can make.
*
*@authors Colin Fang
*
*
*
*/

<<<<<<< HEAD

=======
>>>>>>> c1ffdecb999de77e97fa301b87f0458d32a843f7
#include "AI.h"

//arrays of chess piece positional evaluation


//White King
double evalKW[8][8] = {{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                      {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                      {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                      {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                      {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
                      {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
                      { 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
                      { 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0}};
//Black King
double evalKB[8][8] = {{ 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0},
                       { 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
                       {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
                       {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
                       {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                       {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                       {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
                       {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}};
//White Queen
double evalQW[8][8] = {{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
                      {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
                      {-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
                      {-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
                      { 0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
                      {-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
                      {-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
                      {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}};
//Black Queen
double evalQB[8][8] = {{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
                       {-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
                       {-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
                       { 0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
                       {-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
                       {-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
                       {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
                       {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}};
//White Rook
double evalRW[8][8] = {{ 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
                      { 0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      { 0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0}};
//Black Rook
double evalRB[8][8] = {{ 0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
                      { 0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
                      { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}};
//White Bishop
double evalBW[8][8] = {{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
                      {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
                      {-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
                      {-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
                      {-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
                      {-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
                      {-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
                      {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}};
//Black Bishop
double evalBB[8][8] = {{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
                      {-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
                      {-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
                      {-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
                      {-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
                      {-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
                      {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
                      {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}};
//White Knight
double evalNW[8][8] = {{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
                      {-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
                      {-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
                      {-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
                      {-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
                      {-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
                      {-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
                      {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}};
//Black Knight
double evalNB[8][8] = {{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
                       {-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
                       {-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
                       {-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
                       {-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
                       {-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
                       {-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
                       {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}};
//White Pawn
double evalPW[8][8] = {{ 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
                      { 5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
                      { 1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
                      { 0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
                      { 0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
                      { 0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
                      { 0.5,  1.0,  1.0, -2.0, -2.0,  1.0,  1.0,  0.5},
                      { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}};
//Black Pawn
double evalPB[8][8] = {{ 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
                       { 0.5,  1.0,  1.0, -2.0, -2.0,  1.0,  1.0,  0.5},
                       { 0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
                       { 0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
                       { 0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
                       { 1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
                       { 5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
                      { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}};

AI::AI() = default;



/**@brief A function that starts the Minimax iteration at the root.
*
*@details A function that is only called for the initial board state.
*It gets all the possible valid moves and calls Minimax after making each move.
*When Minimax returns a score, it compares the new score to the best recorded score
*to determine whether it will choose the old board state or the new board state.
*It will then undo the move to return back to the initial board state.
*After looking through each possible valid move, it will return the best move
*as a 4-tuple <start x, start y, end x, end y>
*
*@param depth Used to determine how many turns the AI will look ahead
*@param *board A pointer to the initial board state
*@param color This is the team that the AI is playing, FALSE = black, TRUE = white
*
*@return bestMove This is a 4-tuple <start x, starty, end x, end y> that represents
*the starting and ending position of the best move for the computer player
*/
std::tuple<int, int, int, int> AI::minimaxRoot(int depth, Board *board, bool color){
  	//local variables
    int bestScore = -9999;//initialized at very negative
    int newScore;//used to contain new scores and compare to best score
    std::tuple<int, int, int, int> bestMove;//4-tuple<start x, start y, end x, end y>
    Board *oldBoard = new Board();//saves the initial board state and used to reset the board to the initial state
    board -> stateCopy(oldBoard);
  	//Iterate through the 8x8 matrix to get all valid moves for a specified team
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((board->getTile(i,j)->getPiece() == nullptr) || board->getTile(i,j)->getPiece()->getTeam() != color){
                continue;
            }
          	//locally copy the moves of the specific piece
            std::tuple<int,int> *moves = board->getValidMoves(board->getTile(i,j));
            std::tuple<int,int> validMoves[28];
            for(int k = 0; k < 28; k ++){
                std::get<0>(validMoves[k]) = std::get<0>(*moves);
                std::get<1>(validMoves[k]) = std::get<1>(*moves);
                moves++;
            }
          	//iterate through all the valid moves of the specfic piece
            for(int l = 0; l < 28; l ++){
                if(std::get<0>(validMoves[l]) == -1){
                    break;
                }
                int mvx = std::get<0>(validMoves[l]);
                int mvy = std::get<1>(validMoves[l]);
                std::tuple<int, int, int, int> newMove(i,j,mvx, mvy);
              	//used to reset the mvd bool of the pawn so that it can retain it's ability to jump 2 spaces
                bool mvd = board->getTile(i,j)->getPiece()->getMoved();
                board->move(i, j, mvx, mvy); //move the piece on the virtual board
                if(!board->check(color)){//if the move you are making puts you in check, do not proceed
                    newScore = minimax(depth - 1, board, -10000, 10000, !color);//call minimax on the new boardstate with depth reduced
                    //newScore += rand() % 9;
                    if(newScore >= bestScore ){//if the score of the new board is better than the score of the best board, replace best board with new board
                        bestScore = newScore;
                        bestMove = newMove;
                    }
                }



                oldBoard->stateCopy(board);//undo the move and reset the board to the initial state
                board->getTile(i,j)->getPiece()->setMoved(mvd);//reset the mvd values of the piece

            }
        }
    }
    return bestMove;//return the best move 4-tuple<start x, start y, end x, end y>
}

/**@brief A function that continues the Minimax iteration after the root.
*
*@details A function that is only called after the initial board state.
*It gets all the possible valid moves and calls Minimax(itself) after making each move.
*When Minimax returns a score, it compares the new score to the best recorded score
*to determine whether it will choose the old board state or the new board state.
*It will then undo the move to return back to the initial board state.
*After looking through each possible valid move, it will return the best move
*as a 4-tuple <start x, start y, end x, end y>
*
*@param depth Used to determine how many turns the AI will look ahead
*@param alpha used for Alpha Beta pruning
*@param beta used for Alpha Beta pruning
*@param *board A pointer to the initial board state
*@param color This is the team that the AI is looking at, FALSE = black, TRUE = white
*
*@return bestMove This is an int the score of the best move for the computer player
*/
int AI::minimax(int depth, Board *board, int alpha, int beta, bool color){
    int newScore;//contains the best new score
    if (depth == 0){ //when the algorithm reaches the lowest depth, call the evaluation function on the current board
        return -evaluateBoard(board);
    }
    Board *oldBoard = new Board();//used to reset the board to the initial state
    board -> stateCopy(oldBoard);
	
    if(color == true){//if it is the white player's turn
        int bestMove = -9999;
      	//get all possible valid moves for white
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if((board->getTile(i,j)->getPiece() == nullptr) || board->getTile(i,j)->getPiece()->getTeam() != color){
                    continue;
                }
                std::tuple<int,int> *moves = board->getValidMoves(board->getTile(i,j));
                std::tuple<int,int> validMoves[28];
                for(int k = 0; k < 28; k ++){
                    std::get<0>(validMoves[k]) = std::get<0>(*moves);
                    std::get<1>(validMoves[k]) = std::get<1>(*moves);
                    moves++;
                }
                for(int l = 0; l < 28; l ++){
                    if(std::get<0>(validMoves[l]) == -1){
                        break;
                    }
                    int mvx = std::get<0>(validMoves[l]);
                    int mvy = std::get<1>(validMoves[l]);
                    std::tuple<int, int, int, int> newMove;
                    bool mvd = board->getTile(i,j)->getPiece()->getMoved();
                    board->move(i, j, mvx, mvy);
                    newScore = minimax(depth - 1, board, -10000, 10000, !color);//call minimax on the current board with reduced depth
                  	//store the largest white score in alpha
                    alpha = std::max(alpha, newScore);
                  	//if the largest white score is bigger than the smallest black score, break out of the iteration process
                  	//and return the most recent new score. This white score is larger than the smallest black score, therefore this board state 
                  	//will not be chosen by the black player 
                    if(beta <= alpha){
                        return newScore;
                    }
                    oldBoard ->stateCopy(board);
                    board->getTile(i,j)->getPiece()->setMoved(mvd);

                }
            }
        }
        return newScore;
    }else{//if it is the black player's turn
        int bestMove = 9999;
      	//get all possible valid moves for black
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if((board->getTile(i,j)->getPiece() == nullptr) || board->getTile(i,j)->getPiece()->getTeam() != color){
                    continue;
                }
                std::tuple<int,int> *moves = board->getValidMoves(board->getTile(i,j));
                std::tuple<int,int> validMoves[28];
                for(int k = 0; k < 28; k ++){
                    std::get<0>(validMoves[k]) = std::get<0>(*moves);
                    std::get<1>(validMoves[k]) = std::get<1>(*moves);
                    moves++;
                }
              	//for each valid move
                for(int l = 0; l < 28; l ++){
                    if(std::get<0>(validMoves[l]) == -1){
                        break;
                    }
                    int mvx = std::get<0>(validMoves[l]);
                    int mvy = std::get<1>(validMoves[l]);
                    std::tuple<int, int, int, int> newMove;
                    board->move(i, j, mvx,mvy);
                    newScore = minimax(depth - 1, board, -10000, 10000, !color);//call minimax on the current board with reduced depth
                    beta = std::min(beta, newScore); 
                  	//put the smallest black score into beta
                    //if the smallest black score is less than the largest white score, skip the iteration process
                  	//the white player will not choose this board state as his move
                    if(beta <= alpha){
                        return newScore;
                    }

                }
            }
        }
        return newScore;//return the best new score
    }
}
/**@brief A function that evaluates the score of the current board
*
*@details A function that is called for any board state.
*It gets the score of every piece on the board.
*The score of each piece is calculated by a value based on piece type and an 8x8 double array 
*of positional values located at the top of the code.
*It returns an int that represents the score of the whole board
*
*@param *board A pointer to the current board state
*
*@return totalEvaluation This is an int that represents the score of the whole board
*/
int AI::evaluateBoard(Board *board){
int totalEvaluation = 0;
//iterates through every tile on the board
for(int i = 0; i < 8; i++){
  for(int j = 0; j < 8; j++){
      if(board->getTile(i,j)->getPiece() == nullptr){
          continue;
      }
     //calls getPieceValue function on the piece to get the individual piece value
     //add the individual piece value to totalEvaluation
      totalEvaluation += getPieceValue(board->getTile(i, j)->getPiece(), i, j); 
  }
}
return totalEvaluation;
}

/**@brief A function that evaluates the score of a piece
*
*@details A function that is called in evaluateBoard()
*It gets the score of one piece
*The score of the piece is calculated by a value based on piece type and an 8x8 double array 
*of positional values located at the top of the code.
*It returns an int that represents the score of the piece
*
*@param *piece A pointer to the piece
*@param x the x coordinate of the piece
*@param y the y coordinate of the piece
*
*@return pieceValue This is an int that represents the score of the piece
*/
int AI::getPieceValue(ChessPiece *piece, int x, int y) {
if(piece == nullptr){
return 0;
}
int pieceValue = 0;
//for each piece type, add it's preset piece value and the value found in the 
//8x8 double array at the coordinate of the piece
if(piece->getType() == 'p'){
    if(piece->getTeam()){
        pieceValue = 10 + evalPW[x][y];
    }else {
        pieceValue = 10 + evalPB[x][y];
    }
}else if(piece->getType() == 'r'){
    if(piece->getTeam()){
        pieceValue = 50 + evalRW[x][y];
    }else {
        pieceValue = 50 + evalRB[x][y];
    }
}else if(piece->getType() == 'n'){
    if(piece->getTeam()){
        pieceValue = 30 + evalNW[x][y];
    }else {
        pieceValue = 30 + evalNB[x][y];
    }
}else if(piece->getType() == 'b'){
    if(piece->getTeam()){
        pieceValue = 30 + evalBW[x][y];
    }else {
        pieceValue = 30 + evalBB[x][y];
    }
}else if(piece->getType() == 'q'){
    if(piece->getTeam()){
        pieceValue = 90 + evalQW[x][y];
    }else {
        pieceValue = 90 + evalQB[x][y];
    }
}else if(piece->getType() == 'k'){
    if(piece->getTeam()){
        pieceValue = 900 + evalKW[x][y];
    }else {
        pieceValue = 900 + evalKB[x][y];
    }
}
//all piece values are positive 
//if the piece is black, return the negative of the piece value
if(!piece->getTeam()){
return -pieceValue;
}else{
return pieceValue;
}
}

