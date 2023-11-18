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

std::map<char, int> Blackjack::player_first_hand(){
    std::map<char,int>::iterator itr;
    int randCardIndex;
    for(int i = 0; i < 2; i ++){
        itr = Values_Cards.begin();
        randCardIndex = rand() % Values_Cards.size() - 1;
        std::advance(itr, randCardIndex);
        Players_Hand.insert({itr->first, itr->second});
    }
    show_player_hand();
}

void Blackjack::show_player_hand() {
   std::map<char,int>::iterator itr = Players_Hand.begin();
   std::cout<<"PLAYER'S HAND:"<<std::endl;
   for(; itr != Players_Hand.end(); itr ++)
       std::cout<<itr->first<<" ";
   std::cout<<"\n";
}

void Blackjack::Play(User* user) {

}
