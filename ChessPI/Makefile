all: driver

driver: main.o AI.o Board.o ChessPiece.o Bishop.o Pawn.o Knight.o Rook.o King.o Queen.o Square.o LEDMatrix.o ReedMatrix.o LCDScreen.o lcdDriver.o i2cControl.o
	g++ main.o AI.o Board.o ChessPiece.o Bishop.o Pawn.o Knight.o Rook.o King.o Queen.o Square.o LEDMatrix.o ReedMatrix.o LCDScreen.o lcdDriver.o i2cControl.o -lwiringPi -o chess_pi

main.o: main.cpp
	g++ -c main.cpp

AI.o: AI.cpp
	g++ -c AI.cpp

Board.o: Board.cpp
	g++ -c Board.cpp

ChessPiece.o: ChessPiece.cpp
	g++ -c ChessPiece.cpp

Bishop.o: Bishop.cpp
	g++ -c Bishop.cpp

Pawn.o: Pawn.cpp
	g++ -c Pawn.cpp

Knight.o: Knight.cpp
	g++ -c Knight.cpp

Rook.o: Rook.cpp
	g++ -c Rook.cpp

King.o: King.cpp
	g++ -c King.cpp

Queen.o: Queen.cpp
	g++ -c Queen.cpp

Square.o: Square.cpp
	g++ -c Square.cpp

LEDMatrix.o: LEDMatrix.cpp
	g++ -c LEDMatrix.cpp

ReedMatrix.o: ReedMatrix.cpp
	g++ -c ReedMatrix.cpp

LCDScreen.o:  LCDScreen.cpp
	g++ -c LCDScreen.cpp

lcdDriver.o: lcdDriver.cpp
	g++ -c lcdDriver.cpp

i2cControl.o: i2cControl.cpp
	g++ -c i2cControl.cpp

clean: 
	rm *.o chess_pi