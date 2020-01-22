#include <iostream>
#include "Board.h"
#include "tuple"
#include "AI.h"
#include "LEDMatrix.h"
#include "LCDScreen.h"


/** @brief Helper method to turn user input to coordinates
 *         
 *	
 *  @details given input in the form char,int (e.g. a2), translates that to the coordinates for the boards array of squares
 *	@param char x, int y, represents conventional coordinate system for chess
 *  @return tuple of ints, relating the input to the board coordinates
 */
std::tuple<int,int> translateInput(char x,int y){
    std::tuple<int,int> input;
    std::get<1>(input) = y - 1;
    if(x == 'a'){
        std::get<0>(input) = 0;
    }
    if(x == 'b'){
        std::get<0>(input) = 1;
    }
    if(x == 'c'){
        std::get<0>(input) = 2;
    }
    if(x == 'd'){
        std::get<0>(input) = 3;
    }
    if(x == 'e'){
        std::get<0>(input) = 4;
    }
    if(x == 'f'){
        std::get<0>(input) = 5;
    }
    if(x == 'g'){
        std::get<0>(input) = 6;
    }
    if(x == 'h'){
        std::get<0>(input) = 7;
    }
    return input;
}

/** @brief turns array coordinates into convential chess board coordinates          
 *	
 *  @details given array coordinates, converts them to conventional chess coordinates
 *	@param int x, int y, array coordinates
 *  @return tuple of char and int, corresponding to the chessboard coordinates
 */
std::tuple<char,int> translateOutput(int x,int y){
    std::tuple<char,int> output;
    std::get<1>(output) = y + 1;
    if(x == 0){
        std::get<0>(output) = 'a';
    }
    if(x == 1){
        std::get<0>(output) = 'b';
    }
    if(x == 2){
        std::get<0>(output) = 'c';
    }
    if(x == 3){
        std::get<0>(output) = 'd';
    }
    if(x == 4){
        std::get<0>(output) = 'e';
    }
    if(x == 5){
        std::get<0>(output) = 'f';
    }
    if(x == 6){
        std::get<0>(output) = 'g';
    }
    if(x == 7){
        std::get<0>(output) = 'h';
    }
    return output;
}

/** @brief prints the available moves for a given piece (used for testing)
 *         
 *	
 *  @details loops through valid moves, printing them out, along with information about the piece selected
 *	@param moves, board, x, y, list of valid moves, the board object, and the pieces coordinates
 *  @return true if piece had moves, false otherwise
 */
bool printMoves(std::tuple<int,int> * moves,Board * board, int x, int y){
    std::tuple<char,int> move;
    std::tuple<char,int> piece;
    piece = translateOutput(x,y);
    std::cout << "Piece type ";
    std::cout << board->getTile(x,y)->getPiece()->getType();
    std::cout << " at position ";
    std::cout << std::get<0>(piece);
    std::cout << std::get<1>(piece);
    std::cout << " has the following possible moves" << std::endl;
    if(std::get<0>(*moves) == -1){
        std::cout << "No valid moves" << std::endl;
        return false;
    }
    while(std::get<0>(*moves) != -1){
        move = translateOutput(std::get<0>(*moves),std::get<1>(*moves));
        std::cout<< std::get<0>(move);
        std::cout<< std::get<1>(move) <<std::endl;
        moves++;
    }
    return true;
}

/** @brief method to light up the king if it is put in check
 *         
 *	
 *  @details finds the teams king that is in check, and lights it up
 *	@param LEDm, board, team, the led manager object, the board, and the team that is in check
 * 
 */
void checkLight(LEDMatrix LEDm, Board *board, bool team){
    Square * king = board->findKing(team);
    std::tuple<int,int> location[2];
    std::get<0>(location[0]) = king->getX();
    std::get<1>(location[0]) = king->getY();
    std::get<0>(location[1]) = -1;
    std::get<1>(location[1]) = -1;
    std::tuple<int,int> *ptr = &location[0];
    LEDm.setLEDs(ptr, 2,5,500000);
    
}
/** @brief Gets list of valid moves for a piece
 *         
 *	
 *  @details returns list of moves for a piece
 *	@param board, x,y the board object and the coordinates for the piece
 *  @return pointer to a array of valid moves(tuples)
 */
std::tuple<int,int> * movesList(Board *board, int x, int y){
    return board->getValidMoves(board->getTile(x,y));
}

/** @brief main function for playing chess
 *         
 *
 *  @details creates a board and necessary hardware objects, and allows a player to play against a computer until checkmate occurs
 *
 */


int main() {
    Board *board = new Board();
    AI *comp = new AI();
    LEDMatrix LEDm(8, 8);// Make an LED Matrix object of specified dimensions
    LCDScreen *lcd = new LCDScreen();
    bool turn = true; //true == white, the starting team
    bool checkMate = false;
    int diff;
    std::cout<< "Select Difficulty::  1/2/3/4"<< std::endl;
    std::cin >> diff;

    while(!checkMate){ //main loop for playing the game
        bool check = board->check(turn);
        if(check){ //if a team is in check, checks for a checkmate
            checkLight(LEDm,board, turn);
            if(board->checkmate(turn)){
                if(turn){ 		//white is in checkmate
                    const char * msg = "White lost";
                    std::cout<< msg << std::endl;
                    lcd->printMsg(msg);
                    LEDm.checkMateWhite();
                    break;
                }
                else{			//black is in checkmate
                    const char * msg = "Black lost";
                    std::cout<< msg << std::endl;
                    lcd->printMsg(msg);
                    LEDm.checkMateBlack();
                    break;
                }

            }
            std::cout << "check" << std::endl;
        }
        
        
        bool moved = false;
        
        if(!turn){ //computers turn
            std::cout << "Computer Thinking...." <<std::endl;
            std::tuple<int,int> move[3]; //will contain start position, end position, and a -1 to signal to stop looping when passed to led manager
            std::tuple<int,int,int,int> compMove = comp->minimaxRoot(diff,board,turn); //calls the AI to determing the computers next move
            std::tuple<char,int> compStart = translateOutput(std::get<0>(compMove),std::get<1>(compMove));
            std::tuple<char,int> compEnd = translateOutput(std::get<2>(compMove),std::get<3>(compMove));
            
          	//fill the array to pass to the led manager
            std::get<0>(move[0]) = std::get<0>(compMove);
            std::get<1>(move[0]) = std::get<1>(compMove);
            std::get<0>(move[1]) = std::get<2>(compMove);
            std::get<1>(move[1]) = std::get<3>(compMove);
            std::get<0>(move[2]) = -1;
            std::get<1>(move[2]) = -1;
            //light up the correct tiles
            std::tuple<int,int> * ptr = &move[0];
            LEDm.setLEDs(ptr, 3,4,500000);
          	//print the move as well
            std::cout<< std::get<0>(compStart);
            std::cout<< std::get<1>(compStart);
            std::cout << "  -->  ";
            std::cout<< std::get<0>(compEnd);
            std::cout<< std::get<1>(compEnd) << std::endl;
            moved = true;
          	//perform the move in the board
            board->move(std::get<0>(compMove), std::get<1>(compMove),std::get<2>(compMove),std::get<3>(compMove));
            
        }
        while(!moved){ //loop for player
            char insx = ' ';
            int insy = -1;
            char inex =' ';
            int iney = -1;
            int sx;
            int sy;
            int ex;
            int ey;
            std::cin.clear();
            std::cout << "Input starting x" << std::endl;
            std::cin >> insx;
            if(insx == 'z'){ //test condition, to force a checkmate for testing
                char flag;
                std::cout << "White wins?   y/n" << std::endl;
                std::cin >> flag;
                if(flag != 'n'){
                    board->testCheckmate(true);
                    moved = true;
                    continue;
                }
                
                else{
                    board->testCheckmate(false);
                    moved = true;
                    turn = !turn;
                    continue;
                }
            }
            if(insx == 'x'){
                char flag;
                std::cout << "Reset Board??   y/n" << std::endl;
                std::cin >> flag;
                if(flag == 'y'){
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << "BOARD RESET: NEW GAME";
                    std::cout << std::endl;
                    std::cout << "________________________________________________" <<std::endl;
                    std::cout << "________________________________________________"<<std::endl;
                    std::cout << "________________________________________________"<<std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    
                    board->reset();
                    moved = true;
                    turn = !turn;
                    continue;
                }
                else{
                    continue;
                }
            }
          
            std::cout << "Input starting y" << std::endl;
            std::cin >> insy;
            std::tuple<int,int> start = translateInput(insx,insy);
            sx = std::get<0>(start);
            sy = std::get<1>(start);
            if(board->getTile(sx,sy)->getPiece() == nullptr || board->getTile(sx,sy)->getPiece()->getTeam() != turn){
                std::cout << "invalid selection"<< std::endl;
                continue;
            }
            std::tuple<int,int> * moves = movesList(board,sx,sy);
            if(!printMoves(moves,board,sx,sy)){
                continue;
            }
            //sends all possible moves to led manager for player to see
            LEDm.setLEDs(movesList(board,sx,sy), 28,2,500000);
            std::cin.clear();
            std::cout << "Input ending x" << std::endl;
            std::cin >> inex;
            std::cout << "Input ending y" << std::endl;
            std::cin >> iney;
            
            std::tuple<int,int> end = translateInput(inex,iney);
            ex = std::get<0>(end);
            ey = std::get<1>(end);
            if(!board->move(sx,sy,ex,ey)){
                std::cout << "Invalid Move"<<std::endl;
                continue;
            }
            

            moved = true;

        }

        turn = !turn;
    }


}

