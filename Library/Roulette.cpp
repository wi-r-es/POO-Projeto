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

    colorbet[0] = "black";
    colorbet[1] = "red";
    colorbet[2] = "green";
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
    colorbet[0] = "black";
    colorbet[1] = "red";
    colorbet[2] = "green";
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

string Roulette::simulate_singlebet(){
    int betColorIndex = rand() % 3; // 0 for black, 1 for red, 2 for green
    return colorbet[betColorIndex];
}
// Adicionar seguintes funcionalidades:
/*
 * EVEN OR ODD = X2
 * NUMBER = X3
 * GREEN|0 = X20
 *
 *
 */
void Roulette::Play(User* user) {

    int userMoney = user->getMoney();
    if (userMoney == 0 ) {
        cerr << " user has no more money to bet..." << endl;

        return;
    }
    if ( userMoney <= 5 )
        setBetAmount(1);

     else setBetAmount(static_cast<float>(  randomNumberGeneratorInterval(5, static_cast<int>(userMoney))) );
    //else setBetAmount(static_cast<float>(  rand() % (userMoney + 1) ) ) ;

    //withdraw money for the bet
    user->setMoney(user->getMoney() - getBetAmount());
    // Simulate betting
    short int betNumber = 404;
    string betColor = {};
    bool multibet = false;
    if (getBetAmount() == 1) {
        betColor = simulate_singlebet();
    } else {
        betColor = simulate_singlebet();
        betNumber = rand() % 37;
        multibet = true;
    }
    // Spin the wheel to get the winning number and color
    auto [winNumber, winColor] = oddGenerate();
    if (multibet) {
        cout << "You bet $" << getBetAmount() << " on " << betNumber << betColor << endl;
        cout << "The winning pair is: " << winNumber
             << winColor << "." << endl;
    } else {
        cout << "You bet $" << getBetAmount() << " on " << betColor << endl;
        cout << "The winning pair is: " << winNumber
             << winColor << "." << endl;
    }
    float profit;
    // Determine if the user won or lost and calculate profits
    float amount = getBetAmount();
    if ((multibet && betColor == winColor) || (!multibet && betColor == winColor)) {
        profit = (winColor == "Green") ? amount / 2 * 14 : amount * 2;

        // Check for betNumber
        if (multibet && betNumber == winNumber) {
            profit = amount / 2 * 3;
        }

        /** Additional conditions for odd/even bet can be added here **/

        if (profit) {
            cout << "You won $" << profit << "!" << endl;
            user->setMoney(profit);
        } else {
            cout << "You lost $" << amount << "!" << endl;
        }
    } else {
        cout << "You lost $" << amount << "!" << endl;
    }
    cout << "USER MONEY TO BET: -->" << user->getMoney();


}
