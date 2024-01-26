//
// Created on 06/11/23.
//

#include "Headers/Classic_Slot.h"

ClassicSlot::ClassicSlot(int posX, int posY) : Machine(MACHINE_TYPE::CLASSIC_SLOT, posX, posY) {
    // Initialize the symbols for this classic slot machine
    // static_cast<int>(MACHINE_TYPE::CLASSIC_SLOT);
    numSpins = 0;
}

ClassicSlot::ClassicSlot() : Machine(MACHINE_TYPE::CLASSIC_SLOT, 0,0) {
    // Initialize the symbols for this classic slot machine
    // static_cast<int>(MACHINE_TYPE::CLASSIC_SLOT);
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
    cout << __FUNCTION__ ;

    int userMoney = user->getMoney();
    if (userMoney == 0 ) {
        std::cerr << " user has no more money to bet..." << std::endl;
        if (user->getAttempts() > 5){
            user->addDebt(100);
            user->resetAttempts();
        }
        user->incAttempts();
        return;

    }

    int rol1 = rand() % 4; //randomly a number that represents the 4 simbols
    int rol2 = rand() % 4;
    int rol3 = rand() % 4;


    setBetAmount(userMoney <= 5 ? 1 : static_cast<float>(randomNumberGeneratorInterval(5, static_cast<int>(userMoney))));
    user->setMoney(userMoney - getBetAmount());



    if (rol1 == 7 && rol2 == 7 && rol3 == 7) {
        user->setMoney(userMoney + getBetAmount()*12);
    } else if (rol1 == rol2 && rol2 == rol3) {
        user->setMoney(userMoney + getBetAmount()*4);
    }
    incUsage();
    increaseTemperature();

}

