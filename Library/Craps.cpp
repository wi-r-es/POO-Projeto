//
// Created on 07/11/23.
//

#include "Headers/Craps.h"

Craps::Craps(int posX, int posY) : Machine(MACHINE_TYPE::CRAPS, posX, posY){
    point=0;
    Dice1=0;
    Dice2=0;
}

Craps::~Craps() {

}

void Craps::Play(User* user) {

}
