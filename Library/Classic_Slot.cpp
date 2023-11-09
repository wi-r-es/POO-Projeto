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
    vector<char> possibility = {'F', 'B', 'S', '7'}; // Fruit, Bar, Bell, 7

    int rol1 = rand() % 4;
    int rol2 = rand() % 4;
    int rol3 = rand() % 4;

    int userMoney = user->getMoney();
    int betAmount = rand() % (userMoney + 1);
    user->setMoney(userMoney - betAmount);

    int profit = 0;


    cout << possibility[rol1] << " | " << possibility[rol2] << " | " << possibility[rol3] << endl;

    if (rol1 == rol2 && rol2 == rol3) {
        profit = 100;
    } else if (rol1 == rol2 || rol2 == rol3 || rol1 == rol3) {
        profit = 50;
    }

    user->setMoney(userMoney + profit);

    if (profit > 0) {
        cout << "You won " << profit << "!" << endl;
    } else {
        cout << "You lost " << betAmount << "!" << endl;
    }
}

