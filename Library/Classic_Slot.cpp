//
// Created on 06/11/23.
//

#include "Headers/Classic_Slot.h"

ClassicSlot::ClassicSlot(int posX, int posY) : Machine(MACHINE_TYPE::CLASSIC_SLOT, posX, posY) {
    // Initialize the symbols for this classic slot machine
    numSpins = 0;
}

ClassicSlot::ClassicSlot() : Machine(MACHINE_TYPE::CLASSIC_SLOT, 0,0) {
    // Initialize the symbols for this classic slot machine
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

bool ClassicSlot::Play(User *user) {
    cout << "\n\t[CLASSIC_SLOT]\n" << endl;
    auto start_time = chrono::steady_clock::now();
    int userMoney = user->getMoney();
    if (userMoney == 0 ) {
        std::cerr << "\nuser has no more money to bet..." << std::endl;
        if (user->getAttempts() > 5){
            user->addDebt(100);
            user->resetAttempts();
        }
        user->incAttempts();
        auto end_time = chrono::steady_clock::now();
        auto elapsed = getElapsedTime(start_time, end_time);
        user->incTimeSpent(elapsed);
        return false;
    }

    if(getWinProbability() > 0.7f){
        user->setMoney(user->getMoney() + 200);
        user->incPrizesWon(200);
        incUsage();
        increaseTemperature();
        auto end_time = chrono::steady_clock::now();
        auto elapsed = getElapsedTime(start_time, end_time);
        user->incTimeSpent(elapsed);
        return true;
    }
    /** generate a random number that represents the a symbol **/
    int rol1 = randomNumberGeneratorInterval(1,10);
    int rol2 = randomNumberGeneratorInterval(1,10);
    int rol3 = randomNumberGeneratorInterval(1,10);
    setBetAmount(userMoney <= 5 ? 1 : static_cast<float>(randomNumberGeneratorInterval(5, static_cast<int>(userMoney))));
    user->setMoney(userMoney - getBetAmount());
    user->incBets(1);
    if (rol1==rol2==rol3) {
        auto profit = getBetAmount()*12;
        user->setMoney(userMoney + profit);
        user->incPrizesWon(profit);
        auto end_time = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(start_time - end_time);
        user->incTimeSpent(elapsed);
        return true;
    } else if (rol1==rol2 || rol1==rol3 || rol2==rol3) {
        auto profit = getBetAmount()*4;
        user->setMoney(userMoney + profit);
        user->incPrizesWon(profit);
        auto end_time = chrono::steady_clock::now();
        auto elapsed = getElapsedTime(start_time, end_time);
        user->incTimeSpent(elapsed);
        return true;
    }
    incUsage();
    increaseTemperature();
    auto end_time = chrono::steady_clock::now();
    auto elapsed = getElapsedTime(start_time, end_time);
    user->incTimeSpent(elapsed);
    return false;
}

