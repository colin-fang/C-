#ifndef LCDScreen_H
#define LCDScreen_H
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#define COORDLEN 2


class LCDScreen{
	
public:
	LCDScreen();
	
	virtual ~LCDScreen();
	
	void printMove(char t, bool team, std::tuple<char,int> start, std::tuple<char,int> end);
	void clearLCD();
	void printMsg(const char* c);

private:

};

#endif
