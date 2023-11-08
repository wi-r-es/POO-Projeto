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
/*******************************************************************************************************************************
 * Blackjack Machine ADT class and variables description                                                                       *
 * Inherits UID, TYPE, state, failureProbability, temperate, posX,posY, winProbability, failures and usage from Machine Class  *
 * @see Machine Class                                                                                                          *
 *                                                                                                                             *
 // GUI IDK THIS GAME SO YOU GO SINCE YOU DO
 *******************************************************************************************************************************/
class Blackjack : public Machine {
private:

public:
    /***********************************************************************
     * @brief Constructor for Blackjack Machine                            *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    Blackjack(int posX, int posY);

    /*********************************************
     * @brief Destructor for Blackjack Machine   *
     *********************************************/
    virtual ~Blackjack();

    /**********************************************************************************
     * @brief Function that simulates the operation of the Blackjack Machine .        *
     *                                                                                *
     * @param Debug : boolean that represents if the has to debug or not.             *
     **********************************************************************************/
    void Play(User* user) override;
};


#endif //CODE_BLACKJACK_H
