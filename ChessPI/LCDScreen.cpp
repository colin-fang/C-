#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "LCDScreen.h"
#include "i2cControl.hpp"
#include "lcdDriver.hpp"
#include <chrono>
#include <thread>

#define lcdAdd 0x27 // I2C device address

using namespace std;

LCDScreen::LCDScreen(){
    I2cControl *i2c = new I2cControl(1);
    LcdDriver lcd(lcdAdd, i2c);

    
	
	
	
}

LCDScreen::~LCDScreen(){
    
}

void LCDScreen::clearLCD(){
    I2cControl *i2c = new I2cControl(1);
    LcdDriver lcd(lcdAdd, i2c);
    lcd.clearDisplayClearMem();

}

void LCDScreen::printMove(char t, bool team, std::tuple<char,int> start, std::tuple<char,int> end){
    I2cControl *i2c = new I2cControl(1);
    LcdDriver lcd(lcdAdd, i2c);
    clearLCD();

    lcd.lcdSendCommand(LCD_BEG_LINE_1);
    const char* color[5];
    if(team){
        *color = "White";
    }
    else{
        *color = "Black";
    }
    lcd.lcdString(*color);
    const char * type[6];
    if(t == 'p'){
        *type = "Pawn";
    }
    if(t == 'b'){
        *type = "Bishop";
    }
    if(t == 'r'){
        *type = "Rook";
    }
    if(t == 'n'){
        *type = "Knight";
    }
    if(t == 'q'){
        *type = "Queen";
    }
    if(t == 'k'){
        *type = "King";
    }
    lcd.setCursorPositionRowCol(1,6);
    lcd.lcdString(*color);
    lcd.setCursorPositionRowCol(2,0);
    char beginning[2];
    char b;
    b = std::get<0>(start);
    char beg;
    beg = std::get<1>(start);
    beginning[0] = b;
    beginning[1] = beg;
    const char * ptr;
    ptr = beginning;
    lcd.lcdString(ptr);
    lcd.setCursorPositionRowCol(2,3);
    const char* arrow = "-->";
    lcd.lcdString(arrow);
    lcd.setCursorPositionRowCol(2,7);
    char fin[2];
    char e;
    e = std::get<0>(end);
    char en;
    beg = std::get<1>(end);
    fin[0] = e;
    fin[1] = en;
    const char * eptr;
    eptr = beginning;
    lcd.lcdString(eptr);
}

void LCDScreen::printMsg(const char *c) {
    I2cControl *i2c = new I2cControl(1);
    LcdDriver lcd(lcdAdd, i2c);
    clearLCD();
    lcd.lcdString(c);


}
