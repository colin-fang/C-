#ifndef LEDMatrix_H
#define LEDMatrix_H
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include "tuple"

static const int rowArray[8] = {18, 23, 24, 25, 12, 16, 20, 21};
static const int columnArray[8] = {17, 27, 22, 5, 6, 13, 19, 26};

class LEDMatrix{
	
public:
	LEDMatrix(int x, int y);
	
	virtual ~LEDMatrix();
	
	void reset();

	void setLEDs(std::tuple<int,int> * moves, int m, int loop, int sleep);

	void setLED(int x, int y);
	
	void checkMateBlack();
	void checkMateWhite();

private:
	int xlen;
	int ylen;
	const int* cols;
	const int* rows;
};

#endif
