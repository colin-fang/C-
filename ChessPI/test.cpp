#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include "tuple"
#include "LEDMatrix.h"

int main(int argc, char *argv[])
{   
    // Due to limited physical resources (in order transit) we only made our LED matrix a 4x4 matrix for now. The 8x8 has ben tested by interchanging the LEDs to different circuit locations and it works perfectly. 
    
    LEDMatrix LEDm(8, 8);        // Make an LED Matrix object of specified dimensions
    LEDm.reset();
    std::cout << "hi" <<std::endl;
    while(1){
        LEDm.setLED(0,0);
        
    }
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
                LEDm.setLED(i,j);
                usleep(1000000);
        }
    }
    std::cout << "hello"<< std::endl;
}
