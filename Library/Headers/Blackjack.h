//
// Created by nameless on 06/11/23.
//

/******************************************************************************************
 *  @file Blackjack.h                                                                     *
 *  @brief Class prototypes for Blackjack Machine ADT Structure/Class                     *
 *                                                                                        *
 *  This contains the prototypes for the managing of Blackjack Machines and its fields.   *
 *                                                                                        *
 ******************************************************************************************/

#ifndef CODE_BLACKJACK_H
#define CODE_BLACKJACK_H
#include "Machine.h"
/***********************************************************************************************
 * Blackjack ADT class description derived from Machine                                        *
 *                                                                                             *
 * Inherits from Machine class. Represents a specific type of machine, namely a Blackjack      *
 * game machine. In addition to the attributes inherited from Machine, it includes specific    *
 * attributes and mechanisms for playing the game of Blackjack.                                *
 *                                                                                             *
 * Values_Cards            -> Map associating card characters with their corresponding         *
 *                            integer values in the game of Blackjack.                         *
 *                            For example, 'A' might map to 1 or 11, '2' to 2, ..., 'K' to 10. *
 * Dealers_Hand            -> Vector storing the integer values of the cards currently in the  *
 *                            dealer's hand. Each integer represents a card.                   *
 * Players_Hand            -> Vector storing the integer values of the cards currently in the  *
 *                            player's hand. Similar to Dealers_Hand, each integer             *
 *                            represents a card.                                               *
 ***********************************************************************************************/
class Blackjack : public Machine {
private:
    std::map<char,int> Values_Cards;
    std::vector<int> Dealers_Hand;
    std::vector<int> Players_Hand;
public:
    /***********************************************************************
     * @brief Constructor for Blackjack Machine                            *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    Blackjack(int posX, int posY);

    /*************************************************
     * @brief Empty Constructor for Roulette Machine *
     *************************************************/
    Blackjack();

    /*********************************************
     * @brief Destructor for Blackjack Machine   *
     *********************************************/
    virtual ~Blackjack();

    /***************************************************************
     * @brief Function to print the Blackjack for testing purposes *
     ***************************************************************/
    void printMap() const;

    /***************************************************************
     * @brief Function to hand out cards to a chosen map           *
     ***************************************************************/
    void give_card(std::vector<int>& cards_map);

    /*****************************************************************************************
     * @brief Function that hands out cards to the dealer and player to start the game       *
     *****************************************************************************************/
    void start_game();

    /***************************************************************
     * @brief Function that shows the cards the player has         *
     ***************************************************************/
    void show_player_hand();

    /***************************************************************
     * @brief Function that shows the cards the player has         *
     ***************************************************************/
    void show_dealer_hand();

    /***************************************************************
     * @brief Function that shows the cards on the table           *
     ***************************************************************/
    void show_game();


    /***************************************************************
     * @brief Function that simulates the decision of the player   *
     * to get more cards or stay with the cards he has now         *
     ***************************************************************/
    int  hit_or_stay();

    /***************************************************************
     * @brief Function that simulates one game                     *
     ***************************************************************/
    bool simulate_game();
    /**********************************************************************************
     * @brief Function that simulates the operation of the Blackjack Machine .        *
     *                                                                                *
     * @param Debug : boolean that represents if the has to debug or not.             *
     **********************************************************************************/
    bool Play(User* user) override;

};


#endif //CODE_BLACKJACK_H
