#include <iostream>
#include "Board.h"
#include "tuple"
#include "ReedMatrix.h"



int main() {
    ReedMatrix Reedm(4,4);      // Make a Reed Switch Matrix object of specified dimensions

    //int **ReedArray;
    Reedm.fillMatrix();         // Get Reed Switch data from chess board and fill in the array
    
}
