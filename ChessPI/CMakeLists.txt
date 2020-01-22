cmake_minimum_required(VERSION 3.15)
project(team11)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(team11
        Bishop.cpp
        Bishop.h
        Board.cpp
        Board.h
        ChessPiece.cpp
        ChessPiece.h
        driver.cpp
        i2cControl.cpp
        i2cControl.hpp
        King.cpp
        King.h
        Knight.cpp
        Knight.h
        lcdDriver.cpp
        lcdDriver.hpp
        LCDScreen.cpp
        LCDScreen.h
        LEDMatrix.cpp
        LEDMatrix.h
        main.cpp
        Pawn.cpp
        Pawn.h
        ph.cpp
        practice.cpp
        Queen.cpp
        Queen.h
        readArduino.cpp
        ReedMatrix.cpp
        ReedMatrix.h
        ReedSwitchTest.cpp
        Rook.cpp
        Rook.h
        Square.cpp
        Square.h
        test.cpp AI.cpp AI.h)
