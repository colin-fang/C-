#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <wiringSerial.h>
#include <string.h>
#include <errno.h>
#include "ReedMatrix.h"

ReedMatrix::ReedMatrix(int x, int y){
	ReedMatrix::xlen = x;
	ReedMatrix::ylen = y;
}

ReedMatrix::~ReedMatrix(){
	
}

int** ReedMatrix::fillMatrix(){
	int fd ;
	
	//These lines of code make a 2D array
	int** arr = 0;
	arr = new int*[xlen];
	for (int x = 0; x < xlen; x++){
		arr[x] = new int[ylen];
		for (int y = 0; y < ylen; y++){
			arr[x][y] = x;
		}	
	}

	//Check if the arduino port works
	if((fd=serialOpen("/dev/ttyACM0",9600))<0){
		fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
	}

	serialFlush(fd); // Discard whatever stream of data is left over so we can start from the beginning of the matrix
	for (int x = 0; x < xlen; x++){
		for (int y = 0; y < ylen; y++){
			if(serialGetchar(fd) == 49){ // ASCII char 1 is 49 in dec
				std::cout<< 0 << std::endl;
				//arr[x][y] = 1;
			}
			else{
				std::cout<< 1 << std::endl;
				//arr[x][y] = 0;
			}
		}	
	}
	return arr;
	
}
