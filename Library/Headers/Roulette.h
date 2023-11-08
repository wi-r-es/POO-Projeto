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
#include "Headers/Machine.h"
/*******************************************************************************************************************************
 * Roulette Machine ADT class and variables description                                                                        *
 * Inherits UID, TYPE, state, failureProbability, temperate, posX,posY, winProbability, failures and usage from Machine Class  *
 * @see Machine Class                                                                                                          *
 *                                                                                                                             *
 *
 *******************************************************************************************************************************/
class Roulette {
private:
    // TBD
    //will try to have this done by tomorrow
public:
    /***********************************************************************
     * @brief Constructor for Roulette Machine                             *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    Roulette(int posX, int posY);

    /*********************************************
     * @brief Destructor for Roulette Machine    *
     *********************************************/
    virtual ~Roulette();

    /**********************************************************************************
     * @brief Function that simulates the operation of the Roulette Machine .         *
     *                                                                                *
     * @param Debug : boolean that represents if the has to debug or not.             *
     **********************************************************************************/
    void Play(User* user);
};


#endif //CODE_ROULETTE_H
