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
 * numSpins                ->    not implemented as expected                                  *
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
     * @note This constructor provides a way to create a ClassicSlot machine with default settings. Mostly for testing purposes.
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

    /*******************************************************************************************************************************************************************
     * @brief Simulates a round of play on the ClassicSlot machine for a user.
     *
     * This member function of the `ClassicSlot` class manages the gameplay for a user on the classic slot machine. The function performs several key operations:
     * 1. Checks the user's current monetary balance. If the user has no money, it increases their debt after a certain number of attempts and exits the round.
     * 2. Determines a win based on a predefined probability. If the win condition is met, the user's balance is increased accordingly.
     * 3. Simulates the slot machine spin by generating random numbers to represent slot symbols.
     * 4. Determines the game's outcome based on the alignment of these symbols and updates the user's balance and game statistics.
     * 5. Tracks the time spent by the user in playing the round.
     *
     * The function uses a random number generator for simulating the spinning of slot reels and decides the game outcome based on the matching of symbols.
     * The bet amount is dynamically set based on the user's current money.
     *
     * @note This function is central to the slot machine gameplay, handling the betting process, spin simulation, and outcome determination.
     *
     * @see User class for user-related operations.
     * @see randomNumberGeneratorInterval(), getWinProbability(), getBetAmount(), incUsage(), increaseTemperature() for various utility functions.
     *
     * @param user Pointer to a `User` object representing the player.
     *
     * @exception None. This function does not throw exceptions but relies on methods that might (e.g., random number generation).
     * @exceptsafe This function provides basic exception safety. If an exception is thrown, the user's state remains unchanged.
     *
     * @return bool - The outcome of the round: `true` if the player wins, `false` otherwise.
     *******************************************************************************************************************************************************************/
    bool Play(User* user) override;
};






#endif //CODE_CLASSIC_SLOT_H
