//
// Created on 06/11/23.
//

/*************************************************************************************************
 *  @file Classic_Slot.h                                                                        *
 *  @brief Class prototypes for Classic Slot Machine ADT Structure/Class                         *
 *                                                                                               *
 *  This contains the prototypes for the managing of Classic Slot Machines and its fields.       *
 *                                                                                               *
 *************************************************************************************************/

#ifndef CODE_CLASSIC_SLOT_H
#define CODE_CLASSIC_SLOT_H

#include "Machine.h"


/*******************************************************************************************************************************
 * Classic Slot Machine ADT class and variables description                                                                    *
 * Inherits UID, TYPE, state, failureProbability, temperate, posX,posY, winProbability, failures and usage from Machine Class  *
 * @see Machine Class                                                                                                          *
 *                                                                                                                             *
 * symbols      ->  Symbols in this classic slot machine                                                                       *
 * numSpins     ->  Number of spins played on this machine                                                                     *
 *******************************************************************************************************************************/
class ClassicSlot : public Machine {
private:
    std::vector<std::string> symbols;
    int numSpins;

public:
    /***********************************************************************
     * @brief Constructor for Classic Slot Machine                         *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    ClassicSlot(int posX, int posY);

    /************************************************
     * @brief Destructor for Classic Slot Machine   *
     ************************************************/
    virtual ~ClassicSlot();

    /************************************************
     * @brief Spin the reels of the slot machine    *
     ************************************************/
    void Spin();

    /*******************************************
     * @brief Getter for the number of spins   *
     * @return Number od Spins.                *
     *******************************************/
    int getNumSpins() const;

    // Function to reset the number of spins
    /***************************************************
     * @brief Reset the number of spins of the machine *
     ***************************************************/
    void resetNumSpins();

    /**********************************************************************************
     * @brief Function that simulates the operation of the Machine .                  *
     *                                                                                *
     * @param Debug : boolean that represents if the has to debug or not.             *
     **********************************************************************************/
    void Play(User* user);
};






#endif //CODE_CLASSIC_SLOT_H
