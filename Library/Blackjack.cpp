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
    for (const auto& pair : Values_Cards)
        std::cout << "Card: " << pair.first << " Value: " << pair.second << std::endl;
}

void Blackjack::give_card(std::map<char, int>& cards_map){
    std::map<char,int>::iterator itr = Values_Cards.begin();
    int randCardIndex = randomNumberGeneratorInterval(0, Values_Cards.size() - 1);
    std::advance(itr, randCardIndex);
    cards_map.insert({itr->first, itr->second});

}


void Blackjack::start_game(){
    for(int i = 0; i < 2; i ++){
        give_card(Players_Hand);
        give_card(Dealers_Hand);
    }
    show_player_hand();
    std::cout<<"DEALER'S FIRST HAND"<<std::endl;
    std::cout<<Dealers_Hand.begin()->first<<"| ??"<<std::endl;
}

void Blackjack::show_player_hand() {
    std::cout<<"PLAYER'S HAND:"<<std::endl;
    for(const auto& card : Players_Hand)
        std::cout << card.first << " ";
    std::cout<<"\n";
}

void Blackjack::show_dealer_hand() {
    std::cout<<"DEALER'S HAND:"<<std::endl;
    for(const auto& card : Dealers_Hand)
        std::cout<< card.first << "| ";
    std::cout<<"\n";
}

/** Function to get the sum total of card values **/
int const get_total(std::map<char, int>card_map){
    int total = 0;
    for(const auto& card : card_map)
        total += card.second;
    return total;
}

void Blackjack::show_game(){
    show_player_hand();
    std::cout<<"Total = "<<get_total(Players_Hand)<<std::endl;
    show_dealer_hand();
    std::cout<<"Total = "<<get_total(Dealers_Hand)<<std::endl;
}

int Blackjack::hit_or_stay(){
    int decision = randomNumberGeneratorInterval(0, 1);
    return decision;
}

void Blackjack::simulate_game(){
    int player_total = 0, dealer_total = 0, player_decision;
    bool game = true;
    /** Give the cards to the player and dealer**/
    start_game();

    while(game){
        player_total = get_total(Players_Hand);
        dealer_total = get_total(Dealers_Hand);
        if((player_total >= 21 || dealer_total >= 21) || !player_decision){
            game = false;
        }
        /** Simulates the decision hit or stay in a random manner
         * 1 -> hit
         * 0 -> stay
         * **/
        player_decision = hit_or_stay();
       if(player_decision)
           give_card(Players_Hand);
       show_game();
    }
    std::cout<<"STOPPED"<<std::endl;
    show_game();
}


void Blackjack::Play(User* user) {
    int userMoney = user->getMoney();
    if (userMoney == 0 ) {
        std::cerr << " user has no more money to bet..." << std::endl;
        if (user->getAttempts() > 5) {
            user->addDebt(100);
            user->resetAttempts();
        }
        user->incAttempts();
        return;
    }
}
