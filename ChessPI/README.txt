
Compilation (tested on rasperry pi) :: 
make all

then run:
./chess_pi

NOTE TO SELF: We are using someone's code for the LCD printer and just manipulating it as we need.

Our project is contingent on a physical board made up of a ReedSwitch matrix and an LED Matrix. 
The ReedSwitch matrix is wired to an arduino which takes input and sends it through the usb port to the rasberry pi. We have successfully designed and implemented the circuitry for this.
The LED matrix is controlled by the GPIO of the rasberry pi. We have worked out algorithms to light each LED, successfully designed and implemented the circuitry for this as well.
However, since the physical board is needed to check for new moves and display moves on the physical chess board, we have implemented tests so the TA can see that our program 
works in the software-end of the project. If required, we can send pictures of our physical board to the TA if they wish to ensure that the physical chses board actually works with the software. 


For now, the main file runs several tests to show the movement capabilities of the Chess Pi board.

All positional outputs are formatted as xy

The board is laid out as such (N = knight to avoid confusion with king):
  7 R N B Q K B N R    Black
  6 P P P P P P P P
  5 - - - - - - - -
y 4 - - - - - - - -
  3 - - - - - - - -
  2 - - - - - - - -
  1 P P P P P P P P
  0 R N B Q K B N R
    0 1 2 3 4 5 6 7    White
	    x

The first test prints out all moves for the left white bishop[2,0] (should be none, as it is obstructed)
The second test prints out all moves for the pawn to the right and infront of the bishop[3,1](a pawn that is obstructing the bishop)
		-since the pawn has not moved before, it is able to move 1 or 2 spaces forward
The first test is run again, showing that now that the pawn has moved, the bishop has 5 spaces to move to
The board reset function is then called
the first test is run yet again, and since it is obstructed again, the bishop has no moves
A test for the Knight[1,0] is run, showing its abilities to "jump" over pieces
the pawn at position[2,1] is moved to [2,2]
the knight[1,0] test is run, and the position [2,2] should no longer be an option as it belongs to a friendly piece


