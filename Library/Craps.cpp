//
// Created on 07/11/23.
//

#include "Headers/Craps.h"

Craps::Craps(int posX, int posY) : Machine(MACHINE_TYPE::CRAPS, posX, posY){
    point=0;
    Dice1=0;
    Dice2=0;
}

Craps::Craps(): Machine(MACHINE_TYPE::CRAPS, 0, 0) {
    point=0;
    Dice1=0;
    Dice2=0;
}

Craps::~Craps() {

}

void Craps::RollDices() {
    Dice1 = rand() % 6 + 1;
    Dice2 = rand() % 6 + 1;
}

bool Craps::Play(User* user) {
    int userMoney = user->getMoney();
    if (userMoney == 0 ) {
        std::cerr << "\nuser has no more money to bet..." << std::endl;
        if (user->getAttempts() > 5){
            user->addDebt(100);
            user->resetAttempts();
        }
        user->incAttempts();
        return false;
    }
    if(getWinProbability() > 0.7f){
        user->setMoney(user->getMoney() + 200);
        incUsage();
        increaseTemperature();
        return true;
    }

    setBetAmount(userMoney <= 5 ? 1 : static_cast<float>(randomNumberGeneratorInterval(5, static_cast<int>(userMoney))));

    RollDices();
    int sumDices = Dice1 + Dice2;
    incUsage();
    increaseTemperature();
    if (sumDices == 7 || sumDices == 11) {

        std::cout << "\nYou win!" << std::endl;
        user->setMoney(userMoney + getBetAmount() * 2);
        return true;
    }
    /* else if (sumDices == 2 || sumDices == 3 || sumDices == 12) {

        std::cout << "\nYou lost!" << std::endl;
        user->setMoney(userMoney - getBetAmount());
        return false;
    }
     */
    else {
        return false;
        //std::cout << "\nRoll again!" << std::endl;
    }


}
