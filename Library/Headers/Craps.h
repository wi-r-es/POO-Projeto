//
// Created on 07/11/23.
//

/******************************************************************************************
 *  @file Craps.h                                                                         *
 *  @brief Class prototypes for Craps Machine ADT Structure/Class                         *
 *                                                                                        *
 *  This contains the prototypes for the managing of Craps Machines and its fields.       *
 *                                                                                        *
 ******************************************************************************************/
#ifndef CODE_CRAPS_H
#define CODE_CRAPS_H
#include "Machine.h"
/*******************************************************************************************************************************
 * Craps Machine ADT class and vars description                                                                                *
 * Inherits UID, TYPE, state, failureProbability, temperate, posX,posY, winProbability, failures and usage from Machine Class  *
 * @see Machine Class                                                                                                          *
 *                                                                                                                             *
 *
 *******************************************************************************************************************************/
class Craps : public Machine{
private:
    int point; // The point is the target number in a game of craps.
    unsigned int Dice1 : 4; // 4 bits for value (0 to 15)
    unsigned int Dice2 : 4; // 4 bits for value (0 to 15)

public:
    /***********************************************************************
     * @brief Constructor for Craps Machine                                *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    Craps(int posX, int posY);

    Craps();

    /******************************************
     * @brief Destructor for Craps Machine    *
     ******************************************/
    virtual ~Craps();

    void RollDices();

    /**********************************************************************************
     * @brief Function that simulates the operation of the Craps Machine .            *
     *                                                                                *
     * @param Debug : boolean that represents if the has to debug or not.             *
     **********************************************************************************/
    bool Play(User* user) override ;
};


#endif //CODE_CRAPS_H
