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
#include "User.h"
#include <vector>
#include <random>
#include <iostream>
using namespace std;


/**********************************************************************************************
 * ClassicSlot ADT class description derived from Machine                                     *
 *                                                                                            *
 * Inherits from Machine class. Represents a classic slot machine typically found in casinos. *
 * Classic slot machines are simpler in design and function compared to more modern video     *
 * slot machines, often featuring a limited number of reels and traditional symbols. In       *
 * addition to the attributes inherited from the Machine class, the ClassicSlot class         *
 * includes specific attributes unique to the functioning of a classic slot machine.          *
 *                                                                                            *
 * numSpins                -> An integer representing the number of spins that have been      *
 *                            played on this machine. This is a key statistic for tracking    *
 *                            the usage and popularity of the machine, as well as for         *
 *                            maintenance and analysis purposes.                              *
 *                                                                                            *
 * This class would likely also include methods specific to the operation of a classic slot   *
 * machine, such as handling bets, spinning the reels, determining winning combinations,      *
 * and calculating payouts. These methods would make use of both the inherited attributes     *
 * from the Machine class and the specific attributes of the ClassicSlot class.               *
 **********************************************************************************************/
class ClassicSlot : public Machine {
private:
    int numSpins;

public:
    /***********************************************************************
     * @brief Constructor for Classic Slot Machine                         *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    ClassicSlot(int posX, int posY);

 /****************************************************
     * @brief Empty Constructor for Roulette Machine *
 ****************************************************/
    ClassicSlot();

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
    bool Play(User* user) override;
};






#endif //CODE_CLASSIC_SLOT_H
