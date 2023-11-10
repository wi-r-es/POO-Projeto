//
// Created on 07/11/23.
//
/******************************************************************************************
 *  @file Roulette.h                                                                      *
 *  @brief Class prototypes for Roulette Machine ADT Structure/Class                      *
 *                                                                                        *
 *  This contains the prototypes for the managing of Roulette Machines and its fields.    *
 *                                                                                        *
 ******************************************************************************************/
#ifndef CODE_ROULETTE_H
#define CODE_ROULETTE_H
#include <iostream>
#include <list>
#include <random>
#include <map>
#include <utility>
using namespace std;

#include "Machine.h"
#include "User.h"


/*******************************************************************************************************************************
 * Roulette Machine ADT class and variables description                                                                        *
 * Inherits UID, TYPE, state, failureProbability, temperate, posX,posY, winProbability, failures and usage from Machine Class  *
 * @see Machine Class                                                                                                          *
 *                                                                                                                             *
 *
 *******************************************************************************************************************************/
class Roulette : public Machine {
private:
    map<int, string> BOARD;

    //will try to have this done by tomorrow
public:

    /***********************************************************************
     * @brief Constructor for Roulette Machine                             *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    Roulette(int posX, int posY);
    /*************************************************
     * @brief Empty Constructor for Roulette Machine *
     *************************************************/
    Roulette();

    /*********************************************
     * @brief Destructor for Roulette Machine    *
     *********************************************/
    virtual ~Roulette();


    /***************************************************************
     * @brief Function to print the roulette for testing purposes *
     ***************************************************************/
    void printMap() const;







    /**
     * @
     * @return
     */
    pair<int, string> oddGenerate();
    /**************************************************************************************
     * @brief Function that simulates the operation of the Roulette Machine .             *
     *                                                                                    *
     *        Picks a bet amount for the user, randomly choose a bet amount.              *
     *        Generates the outcome of the round and the success or unsuccess of the bet.  *
     *        Then it adds or not the amount of money to the user.                        *
     *                                                                                    *
     * @see oddGenerate()                                                                 *
     * @param Debug : boolean that represents if the has to debug or not.                 *
     *
     **************************************************************************************/
    void Play(User* user) override ;
};



#endif //CODE_ROULETTE_H
