//
// Created on 07/11/23.
//

#include "Headers/Roulette.h"

Roulette::Roulette(int posX, int posY) : Machine(MACHINE_TYPE::ROULETTE, posX, posY) {

}

Roulette::~Roulette() {

}

void Roulette::Play(User* user) {

    int userMoney = user->getMoney();
    int betAmount = rand() % (userMoney + 1);
    int profit = 0;

    int betColor;
    int randColor = rand() % 100;
    if (randColor < 45) {
        // Red (45% chance)
        betColor = 0;
    } else if (randColor < 90) {
        // Black (45% chance)
        betColor = 1;
    } else {
        // Green (10% chance)
        betColor = 2;
    }

    int winNumber = rand() % 37;


    int winColor;
    int randWinColor = rand() % 100; // Random number between 0 and 99
    if (randWinColor < 45) {
        // Red (45% chance)
        winColor = 0;
    } else if (randWinColor < 90) {
        // Black (45% chance)
        winColor = 1;
    } else {
        // Green (10% chance)
        winColor = 2;
    }

    cout << "You bet $" << betAmount << " on ";

    if (betColor == 0) {
        cout << "red "<< endl;
    } else if (betColor == 1) {
        cout << "black "<<endl;
    } else {
        cout << "green "<<endl;
    }


    cout << "The Color was: ";

    if (winColor == 0) {
        cout << "red ";
    } else if (winColor == 1) {
        cout << "black ";
    } else {
        cout << "green ";
    }

    cout << "and the number was " << winNumber << "." << endl;

    if (betColor == winColor && winColor != 2) {
        profit += betAmount * 2;
        cout << "You won $" << profit << "!" << endl;
        user->setMoney(userMoney + profit);
    } else if (betColor == winColor && winColor == 2) {
        profit += betAmount * 20;
        cout << "You won $" << profit << "!" << endl;
        user->setMoney(userMoney + betAmount);
    } else {
        cout << "You lost $" << betAmount << "!" << endl;
    }

}
