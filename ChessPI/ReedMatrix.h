#ifndef ReedMatrix_H
#define ReedMatrix_H
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

class ReedMatrix{
	
public:
	ReedMatrix(int x, int y);
	
	virtual ~ReedMatrix();
	
	int** fillMatrix();


private:
	int xlen;
	int ylen;
};

#endif
