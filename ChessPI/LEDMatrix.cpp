/** @brief The LEDMatrix class that is used by the program to manipulate the LEDMatrix
 *         
 *
 * @details The LEDMatrix for the Chessboard is an 8x8 set of LEDs. When an instance of this class is created, it can be manipulated in order to light specific LEDs. 
 * @authors Jermiah Joseph
 */


#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "LEDMatrix.h"
#include "tuple"

using namespace std;

const int coordlen = 2; 						// a pair of coordinates has length 2

/** @brief The LEDMatrix class constructor. When an instance of this class is created, it builds an LED matrix to be manipulated.
 *         
 *
 *  @details This constructor sets up the matrix so that the functions can use it. 
 * 	It first tries to setup the wiring of the GPIO, and then sets each of the pins that the LEDMatrix connects to, to OUTPUT. 
 * 	@param x,y The constructor takes x and y integers that represent the dimensions of the board (i.e an 8x8 board would mean x=8 and y =8).
 */

LEDMatrix::LEDMatrix(int x, int y){
	LEDMatrix::xlen = x;
	LEDMatrix::ylen = y;
	LEDMatrix::cols = columnArray;
	LEDMatrix::rows = rowArray;
	if(wiringPiSetupGpio() == -1){ 				// when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
	}
	for(int i=0; i < LEDMatrix::xlen ; i++){
		pinMode(LEDMatrix::cols[i], OUTPUT);	// initialize each of the RasberryPi GPIO pins that are connected to the LEDMatrix columns to 0
	}
	for(int j=0; j < LEDMatrix::xlen ; j++){
		pinMode(LEDMatrix::rows[j], OUTPUT);	// initialize each of the RasberryPi GPIO pins that are connected to the LEDMatrix rows to 0
	}
}

LEDMatrix::~LEDMatrix(){
	
}

/** @brief reset method that will turn off the LEDs that may be on. 
 *         
 *
 *  @details this reset method is utilized in every manipulation of the LEDMatrix. When an LED is turned on, it will stay on until it is turned off. Therefore, if we want to switch on another LED, we reset the board using this method. 
 * More specifically, it sets the anode and cathode of each LED to 1 (no flow of current). 
 * 	@param No parameters are given to this method.
 */
void LEDMatrix::reset(){
	for(int i=0; i < LEDMatrix::xlen ; i++){
		digitalWrite(LEDMatrix::cols[i], 1);		// Set anode of each LED to 1
	}
	for(int j=0; j < LEDMatrix::xlen ; j++){
		digitalWrite(LEDMatrix::rows[j], 1);		// Set cathode of each LED to 1
	}
	
}

/** @brief setLEDs method iterates through a list of positions and lights the LEDs of those positions. 
 *         
 *
 *  @details this setLEDs method will light a given set of LEDs in the matrix, lighting each one-by-one. 
 * 	@param tuple<int,int> the first parameter is a pointer to a tuple of ints which represent the x,y coordinates of the LEDs that are to be lit in the matrix. 
 * 	@param m The int m is simply the number of LEDs to be lit. 
 * 	@param loop The loop integer represents the number of times the LEDs are lit (i.e if two LEDs are to be lit, and loop = 2, each of the two LEDs will be lit twice. 
 * 	@param sleep The sleep integer represents the number of microseconds that each LED will be lit for (note: there are 1 million (1000000) microseconds in 1 second).
 */
void LEDMatrix::setLEDs(std::tuple<int,int> * moves, int m, int loop, int sleep){
	LEDMatrix::reset();
	int i, j;
    if(std::get<0>(*moves) == -1){
        std::cout << "No valid moves" << std::endl;			// Check if there are any valid moves (the first element of the tuple is -1)		
    }
    std::tuple<int,int> validMoves[m];						// Create another tuple of ints that will be iterated through
    for(int k = 0; k < m; k ++){
         std::get<0>(validMoves[k]) = std::get<0>(*moves);	// Copy the x coordinate of each tuple
         std::get<1>(validMoves[k]) = std::get<1>(*moves);	// Copy the y coordinate of each tuple
         moves++;
    }
    for(int i = 0; i < loop; i++){
		for(int j = 0; j < m; j++){
			if(std::get<0>(validMoves[j]) == -1){			// Check again that there are valid moves to iterate through
				break;
			}
			LEDMatrix::setLED(std::get<0>(validMoves[j]), std::get<1>(validMoves[j]));	// Iterate through the tuple and provide each x,y pair to the setLED method
			
			usleep(sleep);									// Let the LED stay lit for sleep microseconds (input)
			LEDMatrix::reset();
		}
	}
}

/** @brief checkMateBlack method is called when Black is in checkmate (when white wins) that lights up all the LEDs in the board.
 *         
 *
 *  @details this checkMateBlack method will light all the LEDs on the board when black is in checkmate. The LEDs that are lit start on the side of black and then move towards white's direction.
 */
void LEDMatrix::checkMateBlack(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j<8; j++){
			setLED(j,i);
			usleep(20000);									// Set each LED in the matrix starting from the black side
		}
	}

}

/** @brief checkMateWhite method is called when White is in checkmate (when black wins) that lights up all the LEDs in the board.
 *         
 *
 *  @details this checkMateWhite method will light all the LEDs on the board when White is in checkmate. The LEDs that are lit start on the side of White and then move towards black's direction.
 */
void LEDMatrix::checkMateWhite(){
	for(int i = 7; i >= 0; i--){
		for(int j = 7; j >= 0; j--){
			setLED(j,i);
			usleep(20000);									// Set each LED in the matrix starting from the white side
		}
	}

}

/** @brief The setLED method lights a single LED in the matrix.
 *         
 *
 *  @details this setLED method is used by the other methods of this LEDMatrix class to light a single LED given it's coordinates. 
 * 	In order to do this, it sets the cathode for each row to 0 EXCEPT the row in which the LED is in. It then sets the anode for the column the LED is in, to 0 as well. 
 * 	This allows for current to flow but only for the LED that is to be lit. 
 * 	@param x,y This method takes an int x and an int y as parameters which represent the coordinates of the LED that is to be lit. 
 */
void LEDMatrix::setLED(int x, int y){
	LEDMatrix::reset();
	for(int i=0; i < LEDMatrix::ylen ; i++){
		if(y != i){
			digitalWrite(LEDMatrix::rows[i], 0);				// Set the rows of all but the row the LED is in, to 0. This means that current can only flow from the row of the LED (which is set to 1). 
		}
	}				
	digitalWrite(LEDMatrix::cols[x], 0);						// Set the column of the LED to 0, which means that current flows from the row it is in (set to 1) and the column (set to 0). Every other column should be set to 1. 
}
