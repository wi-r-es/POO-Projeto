//
// Created on 07/11/23.
//


#include "Headers/Roulette.h"

Roulette::Roulette(int posX, int posY) : Machine(MACHINE_TYPE::ROULETTE, posX, posY) {
    /** Initialize the map with black numbers **/
    for (int number : {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35}) {
        BOARD[number] = "black";
    }
    /** Initialize the map with red numbers **/
    for (int number : {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}) {
        BOARD[number] = "red";
    }
    BOARD[0]="green";

    colorbet[0] = "black";
    colorbet[1] = "red";
}

Roulette::Roulette() : Machine(MACHINE_TYPE::ROULETTE, 0, 0) {

    for (int number : {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 29, 31, 33, 35}) {
        BOARD[number] = "black";
    }
    /** Initialize the map with red numbers **/
    for (int number : {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}) {
        BOARD[number] = "red";
    }
    BOARD[0]="green";
    colorbet[0] = "black";
    colorbet[1] = "red";
}

Roulette:: ~Roulette()= default;

// was used for debug purposes
void Roulette::printMap() const {
    for (const auto& pair : BOARD) {
        cout << "Number: " << pair.first << " Color: " << pair.second << endl;
    }
}

pair<int, string> Roulette::oddGenerate() {
    int winningNumber = randomNumberGeneratorInterval(0,36); /** possible slots (0 to 36) **/
    string color;

    for (const auto& pair : BOARD) {
        if (pair.first == winningNumber)
            color = pair.second;
    }

    cout <<  "Number: " << winningNumber << " Color: " << color << endl;
    return {winningNumber, color};
}

string Roulette::simulate_singlebet(){
    int betColorIndex = randomNumberGeneratorInterval(0,1); // 0 for black, 1 for red
    return colorbet[betColorIndex];
}

// Adicionar seguintes funcionalidades:
/*
 * EVEN OR ODD = X2
 * NUMBER = X3
 * GREEN|0 = X20
 */

bool Roulette::Play(User* user) {
    auto start_time = std::chrono::steady_clock::now();
    int userMoney = user->getMoney();
    if (userMoney == 0 ) {
        cerr << "\nuser has no more money to bet..." << endl;
        if (user->getAttempts() > 5){
            user->addDebt(100);
            user->resetAttempts();
        }
        user->incAttempts();
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed = getElapsedTime(start_time, end_time);
        user->incTimeSpent(elapsed);
        return false;
    }
    user->incBets(1);
    if(getWinProbability() > 0.7f){
        user->setMoney(user->getMoney() + 200);
        user->incPrizesWon(200);
        incUsage();
        increaseTemperature();
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed = getElapsedTime(start_time, end_time);
        user->incTimeSpent(elapsed);
        return true;
    }
    /** Set bet amount **/
    setBetAmount(userMoney <= 5 ? 1 : static_cast<float>(randomNumberGeneratorInterval(5, static_cast<int>(userMoney))));

    /** withdraw money for the bet **/
    user->setMoney(user->getMoney() - getBetAmount());
    /** Simulate betting **/

    bool multibet = (getBetAmount() != 1);
    string betColor = simulate_singlebet();
    int betNumber = (multibet) ? randomNumberGeneratorInterval(0,36) : 404;

    /**  Spin the wheel to get the winning number and color **/
    auto [winNumber, winColor] = oddGenerate();
    /** Print bets **/
    if (multibet)
        cout << "You bet $" << getBetAmount() << " on " << betNumber << betColor << endl;
    else
        cout << "You bet $" << getBetAmount() << " on " << betColor << endl;

    /** Print winning pair **/
    cout << "The winning pair is: " << winNumber
         << winColor << "." << endl;

    float profit=0;
    float amount = getBetAmount();
    /**  Determine if the user won or lost and calculate profits **/
    if (multibet) {
        if (betColor == winColor)
            profit += amount * 2; // cause  amount / 2 * 4 = *2
        if (betNumber == winNumber)
            profit += (winNumber == 0) ? amount * 10 : amount * 2; // cause  amount / 2 * 20 = *10
        /** Additional conditions for odd/even bet can be added here **/
    } else{
        if (betColor == winColor)
            profit += amount * 2; // cause  amount / 2 * 4 = *2
    }
    incUsage();
    increaseTemperature();
    if (static_cast<bool>(profit)) {
        cout << "You won $" << profit << "!" << endl;
        user->incPrizesWon(profit);
        user->setMoney(user->getMoney() + profit);
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed = getElapsedTime(start_time, end_time);
        user->incTimeSpent(elapsed);
        return true;
    }else {
        cout << "You lost $" << amount << "!" << endl;
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed = getElapsedTime(start_time, end_time);
        user->incTimeSpent(elapsed);
        return false;
    }
    //cout << "\nUSER MONEY TO BET: -->" << user->getMoney();

}
