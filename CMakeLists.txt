cmake_minimum_required(VERSION 3.26)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(code main.cpp
        Library/Machine.cpp
        Library/Headers/Machine.h
        Library/Casino.cpp
        Library/Headers/Casino.h
        Library/User.cpp
        Library/Headers/User.h
        Library/Classic_Slot.cpp
        Library/Headers/Classic_Slot.h
        Library/Blackjack.cpp
        Library/Headers/Blackjack.h
        Library/Roulette.cpp
        Library/Headers/Roulette.h
        Library/Craps.cpp
        Library/Headers/Craps.h
        Library/XML.cpp
        Library/Headers/XML.h
        Library/UsefulFunctions.cpp
        Library/Headers/UsefulFunctions.h
        Library/Headers/kbhitmodule.h)
