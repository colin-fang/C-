#include "LEDMatrix.h"
#include "ReedMatrix.h"

int main(int argc, char *argv[]){
	
	LEDMatrix LEDm(4,4);
	int arr[][COORDLEN] = {{1,2}, {2,1}, {0,0}, {3,3}};
	LEDm.setLEDs(arr, 4);
	return 0;
}
