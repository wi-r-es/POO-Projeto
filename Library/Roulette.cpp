//
// Created on 07/11/23.
//


#include "Headers/Roulette.h"

Roulette::Roulette(int posX, int posY) : Machine(MACHINE_TYPE::ROULETTE, posX, posY) {

}

Roulette::~Roulette() {

}

void Roulette::Play(User* user) {

    vector <int> blackNumbers = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 29, 31, 33, 35};

    vector <int> redNumbers = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};


    int aux = rand() % 17;
    int userMoney = user->getMoney();
    int betAmount = rand() % (userMoney + 1);
    int profit = 0;
    int betColor;
    int randColor = rand() % 100;
    int winNumber;
    int winColor;


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



    int randWinColor = rand() % 100; // Random number between 0 and 99
    if (randWinColor < 45) {
        // Red (45% chance)
        winColor = 0;
        winNumber = redNumbers[aux];

    } else if (randWinColor < 90) {
        // Black (45% chance)
        winColor = 1;
        winNumber = blackNumbers[aux];
    } else {
        // Green (10% chance)
        winColor = 2;
        winNumber = 0;

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
        winNumber = redNumbers[aux];
        
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
