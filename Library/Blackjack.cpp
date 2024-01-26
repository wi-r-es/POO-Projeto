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

void Blackjack::give_card(std::vector<int>& hand){
    auto itr = Values_Cards.begin();
    int randCardIndex = randomNumberGeneratorInterval(0, Values_Cards.size() - 1);
    std::advance(itr, randCardIndex);
    hand.push_back(itr->second);

}


void Blackjack::start_game(){
    for(int i = 0; i < 2; i ++){
        give_card(Players_Hand);
        give_card(Dealers_Hand);
    }
    show_player_hand();
    std::cout<<"DEALER'S FIRST HAND"<<std::endl;
    std::cout<<Dealers_Hand.at(0)<<"| ?? \n\n"<<std::endl;
}

void Blackjack::show_player_hand() {
    std::cout<<"PLAYER'S HAND:"<<std::endl;
    for(const auto& card : Players_Hand)
        std::cout << card << "| ";
    std::cout<<"\n";
}

void Blackjack::show_dealer_hand() {
    std::cout<<"DEALER'S HAND:"<<std::endl;
    for(const auto& card : Dealers_Hand)
        std::cout<< card << "| ";
    std::cout<<"\n";
}

/** Function to get the sum total of card values **/
int get_total(std::vector<int>hand) {
    int total = 0;
    bool has_ace = false;
    for(const auto& card : hand) {
        total += card;
        if(card == 1)
            has_ace = true;
    }

    if(total + 10 <= 21 && has_ace)
       total += 10;

    return total;
}


// A 2 3
// 1+2+3 = 6 < 21       6 + 11 < 21
// 11+2+3 = 16
// A 4 7
// 1+4+7 = 12
// 11+4+7 = 23
void Blackjack::show_game(){
    show_player_hand();
    std::cout<<"Total = "<<get_total(Players_Hand)<<std::endl;
    show_dealer_hand();
    std::cout<<"Total = "<<get_total(Dealers_Hand)<<std::endl;
    std::cout<<"\n";

}

int Blackjack::hit_or_stay(){
    int decision = randomNumberGeneratorInterval(0, 1);
    return decision;
}
// chnge this to bool, so if true player won, if false player lost
bool Blackjack::simulate_game(){
    int player_total = 0, dealer_total = 0, player_decision;
    bool game = true, result;
    /** Give the cards to the player and dealer**/
    start_game();

    while(game){
        if(get_total(Players_Hand) > 21){
            std::cout << "PLAYER LOSES" << std::endl;
            return false;
            game = false;
        }else {
            /** Simulates the decision hit or stay in a random manner
             * 1 -> hit
             * 0 -> stay
             * **/
            player_decision = hit_or_stay();

            if (!player_decision) {
                std::cout << "\n\tSTAY" << std::endl;
                /** Dealer hits until the total on the table is at least 17 **/
                while(true){
                    if(get_total(Dealers_Hand) > 17){
                        break;
                    }
                    std::cout << "\n-> Dealer is hitting..." << std::endl;
                    give_card(Dealers_Hand);
                    show_game();
                }
                if(get_total(Dealers_Hand) > 21){
                    std::cout << "PLAYER WINS" << std::endl;
                    return true;
                }
                game = false;
            } else {
                give_card(Players_Hand);
                std::cout << "\n\tHIT" << std::endl;
            }
            show_game();
        }
    }
    std::cout << "FINAL" << std::endl;
    show_game();

    //Checks who has the bigger value in their hands
    auto p_hand = get_total(Players_Hand);
    auto d_hand = get_total(Dealers_Hand);

    if(p_hand > d_hand) {
        std::cout << "WINNER = [Player]" << std::endl;
        return true;
    }
    /*
    else if(p_hand == d_hand){
        std::cout << "DRAW" << std::endl;
        simulate_game();
    }
     */
    else {
        std::cout << "WINNER = [Dealer]" << std::endl;
        return false;
    }
}


bool Blackjack::Play(User* user) {
    int userMoney = user->getMoney();
    if (userMoney == 0 ) {
        std::cerr << "\n user has no more money to bet..." << std::endl;
        if (user->getAttempts() > 5) {
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
    simulate_game();
    incUsage();
    increaseTemperature();
    return true;
}
