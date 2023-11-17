//
// Created on 06/11/23.
//

#include "Headers/Blackjack.h"

Blackjack::Blackjack(int posX, int posY) : Machine(MACHINE_TYPE::BLACKJACK, posX, posY) {
    /** Initialize the map with**/
    for (char card : {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K'}) {
        if(card == 'A')
            Values_Cards[card] = 1;
        else
            Values_Cards[card] = (card == 'J' || card == 'Q' || card == 'K') ? 10 : (card - '0');
    }
}

Blackjack::Blackjack() : Machine(MACHINE_TYPE::BLACKJACK, 0, 0) {
    /** Initialize the map with**/
    for (char card : {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K'}) {
        if(card == 'A')
            Values_Cards[card] = 1;
        else
            Values_Cards[card] = (card == 'J' || card == 'Q' || card == 'K') ? 10 : (card - '0');
    }
}

Blackjack::~Blackjack() {

}

void Blackjack::printMap() const {
    for (const auto& pair : Values_Cards) {
        std::cout << "Card: " << pair.first << " Value: " << pair.second << std::endl;
    }
}

void Blackjack::Play(User* user) {

}
