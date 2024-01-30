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
 * numSpins                ->                                                                 *
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
    /*******************************************************************************************************************************************************************
     * @brief Constructor for ClassicSlot with position parameters.
     *
     * This constructor initializes an instance of the `ClassicSlot` class, which is derived from the `Machine` class. It sets the machine's type to `CLASSIC_SLOT`
     * and initializes its position to the provided coordinates (`posX`, `posY`). It also initializes the number of spins (`numSpins`) to zero.
     *
     * @note This constructor is used when the position of the slot machine is known and needs to be specified.
     *
     * @see Machine class for the base class constructor.
     *
     * @param posX The x-coordinate of the slot machine's position.
     * @param posY The y-coordinate of the slot machine's position.
     *
     * @exception None. This constructor does not throw exceptions.
     * @exceptsafe This constructor is exception-neutral and offers no guarantees if an exception is thrown during initialization.
     *
     * @return None. Constructors do not return values.
     *******************************************************************************************************************************************************************/
    ClassicSlot(int posX, int posY);

    /*******************************************************************************************************************************************************************
     * @brief Default Constructor for ClassicSlot.
     *
     * This default constructor initializes an instance of the `ClassicSlot` class with default values. It sets the machine type to `CLASSIC_SLOT` and initializes
     * its position to (0, 0). It also sets the number of spins (`numSpins`) to zero. This constructor is used when no specific position is provided for the slot
     * machine.
     *
     * @note This constructor provides a way to create a ClassicSlot machine with default settings.
     *
     * @see Machine class for the base class constructor.
     *
     * @exception None. This constructor does not throw exceptions.
     * @exceptsafe This constructor is exception-neutral and offers no guarantees if an exception is thrown during initialization.
     *
     * @return None. Constructors do not return values.
     *******************************************************************************************************************************************************************/
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
