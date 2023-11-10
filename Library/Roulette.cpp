//
// Created on 07/11/23.
//


#include "Headers/Roulette.h"

Roulette::Roulette(int posX, int posY) : Machine(MACHINE_TYPE::ROULETTE, posX, posY) {
    // Initialize the map with black numbers
    for (int number : {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35}) {
        BOARD[number] = "black";
    }
    // Initialize the map with red numbers
    for (int number : {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}) {
        BOARD[number] = "red";
    }
    BOARD[0]="green";
}

Roulette::Roulette() : Machine(MACHINE_TYPE::ROULETTE, 0, 0) {

    for (int number : {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 29, 31, 33, 35}) {
        BOARD[number] = "black";
    }
    // Initialize the map with red numbers
    for (int number : {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}) {
        BOARD[number] = "red";
    }
    BOARD[0]="green";
}

Roulette:: ~Roulette(){

}

void Roulette::printMap() const {
    for (const auto& pair : BOARD) {
        cout << "Number: " << pair.first << " Color: " << pair.second << endl;
    }
}

pair<int, string> Roulette::oddGenerate() {
    int winningNumber = rand() % 37; // 37 possible slots (0 to 36)
    string color;

    for (const auto& pair : BOARD) {
        if (pair.first == winningNumber)
            color = pair.second;
    }

    cout <<  "Number: " << winningNumber << " Color: " << color << endl;
    return {winningNumber, color};
}

// Adicionar seguintes funcionalidades:
/*
 * EVEN OR ODD = X2
 * NUMBER = X3
 * GREEN|0 = X20
 */
void Roulette::Play(User* user) {
    int userMoney = user->getMoney();
    // restrain the bet amount somehow
    float betAmount = rand() % (userMoney + 1);

    // Simulate betting on a color
    int betNumber = rand() % 37;
    int betColorIndex = rand() % 3; // 0 for red, 1 for black, 2 for green
    string betColors[3] = {"Red", "Black", "Green"};
    string betColor = betColors[betColorIndex];

    // Spin the wheel to get the winning number and color
    auto [winNumber, winColor] = oddGenerate();

    cout << "You bet $" << betAmount << " on " << betNumber << betColor << endl;
    cout << "The winning pair is: " << winNumber
              << winColor << "." << endl;
    float profit;
    // Determine if the user won or lost and calculate profits
    if (betColor == winColor || betNumber == winNumber) {
        if (winColor == "Green") {
           profit = betAmount * 14; // Green typically pays 14:1
        } else {
            profit = betAmount * 2; // Red or Black typically pays 1:1
        }
        std::cout << "You won $" << profit << "!" << std::endl;
        user->setMoney(static_cast<float>(userMoney) + static_cast<float> (profit));
    } else {
        std::cout << "You lost $" << betAmount << "!" << std::endl;
        user->setMoney(static_cast<float>(userMoney) - static_cast<float>(betAmount));
    }
}

