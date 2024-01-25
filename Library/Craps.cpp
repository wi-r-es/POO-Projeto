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

void Craps::Play(User* user) {
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
    setBetAmount(userMoney <= 5 ? 1 : static_cast<float>(randomNumberGeneratorInterval(5, static_cast<int>(userMoney))));

    RollDices();
    int sumDices = Dice1 + Dice2;

    if (sumDices == 7 || sumDices == 11) {

        std::cout << "You win!" << std::endl;
        user->setMoney(userMoney + getBetAmount() * 2);
    } else if (sumDices == 2 || sumDices == 3 || sumDices == 12) {

        std::cout << "You lost!" << std::endl;
        user->setMoney(userMoney - getBetAmount());
    } else {

        std::cout << "Roll again!" << std::endl;
    }
    setTemperature(this->getTemperature() + 0.3);
    increaseTemperature();

}
