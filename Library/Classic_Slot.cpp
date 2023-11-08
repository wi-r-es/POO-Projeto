//
// Created on 06/11/23.
//

#include "Headers/Classic_Slot.h"

ClassicSlot::ClassicSlot(int posX, int posY) : Machine(MACHINE_TYPE::CLASSIC_SLOT, posX, posY) {
    // Initialize the symbols for this classic slot machine
    // static_cast<int>(MACHINE_TYPE::CLASSIC_SLOT);
    symbols = {"FRUIT", "BAR", "BELL", "SEVEN"};
    numSpins = 0;
}

ClassicSlot::~ClassicSlot(){

}

void ClassicSlot::Spin() {
    // Implementation of spinning logic here
    // For now just incrementing the spin count
    numSpins++;
}

int ClassicSlot::getNumSpins() const {
    return numSpins;
}

void ClassicSlot::resetNumSpins() {
    numSpins = 0;
}

void ClassicSlot::Play(User *user) {

}
