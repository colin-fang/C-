#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <wiringSerial.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main(void){
  int fd ;

  if((fd=serialOpen("/dev/ttyACM0",9600))<0){
    fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
    return 1;
  }

  for (;;){
    putchar(serialGetchar(fd));
    fflush(stdout);
  }

	return 0;
}
