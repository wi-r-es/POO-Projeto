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
/**********************************************************************************************
 * Craps ADT class description derived from Machine                                           *
 *                                                                                            *
 * Inherits from Machine class. Represents a Craps game machine typically found in casinos.   *
 * Craps is a dice game where players bet on the outcome of the roll, or a series of rolls,   *
 * of a pair of dice. In addition to the attributes inherited from the Machine class, the     *
 * Craps class includes specific attributes unique to the mechanics of a Craps game.          *
 *                                                                                            *
 * Dice1                  -> An unsigned integer, stored in 4 bits, representing the value    *
 *                           of the first dice. The 4-bit storage allows values from 0 to 15, *
 *                           although in a standard Craps game, the values will range from 1  *
 *                           to 6. This compact representation is efficient in terms of       *
 *                           memory usage.                                                    *
 *                                                                                            *
 * Dice2                  -> Similar to Dice1, this is an unsigned integer for the value of   *
 *                           the second dice, also stored in 4 bits. It serves the same       *
 *                           purpose as Dice1, contributing to the dice roll outcomes in the  *
 *                           game.                                                            *
 *                                                                                            *
 **********************************************************************************************/
class Craps : public Machine{
private:
    unsigned int Dice1 : 4; // 4 bits for value (0 to 15)
    unsigned int Dice2 : 4; // 4 bits for value (0 to 15)

public:
    /********************************************************************************************************************************************************************
     * @brief Constructor for Craps with position parameters.                                                                                                           *
     *                                                                                                                                                                  *
     * This constructor initializes an instance of the `Craps` class, which is derived from the `Machine` class. It sets the machine's type to `CRAPS` and              *
     * initializes its position to the provided coordinates (`posX`, `posY`). Additionally, it initializes the dice values (`Dice1` and `Dice2`) to zero.               *
     *                                                                                                                                                                  *
     * @param posX The x-coordinate of the craps table's position.                                                                                                      *
     * @param posY The y-coordinate of the craps table's position.                                                                                                      *
     *                                                                                                                                                                  *
     * @exception None. This constructor does not throw exceptions.                                                                                                     *
     * @exceptsafe This constructor is exception-neutral and offers no guarantees if an exception is thrown during initialization.                                      *
     *                                                                                                                                                                  *
     * @return None. Constructors do not return values.                                                                                                                 *
     ********************************************************************************************************************************************************************/
    Craps(int posX, int posY);

    /********************************************************************************************************************************************************************
     * @brief Default Constructor for Craps.                                                                                                                            *
     *                                                                                                                                                                  *
     * This default constructor initializes an instance of the `Craps` class with default position values (0, 0) and sets the machine type to `CRAPS`. It also          *
     * initializes the dice values (`Dice1` and `Dice2`) to zero. This constructor is used when no specific position is provided for the craps table.                   *
     *                                                                                                                                                                  *
     * @note This constructor provides a way to create a Craps table with default settings. Mostly for testing purposes.                                                *
     *                                                                                                                                                                  *
     * @exception None. This constructor does not throw exceptions.                                                                                                     *
     * @exceptsafe This constructor is exception-neutral and offers no guarantees if an exception is thrown during initialization.                                      *
     *                                                                                                                                                                  *
     * @return None. Constructors do not return values.                                                                                                                 *
     ********************************************************************************************************************************************************************/
    Craps();

    /******************************************
     * @brief Destructor for Craps Machine    *
     ******************************************/
    virtual ~Craps();

    /********************************************************************************************************************************************************************
     * @brief Simulates the rolling of dice in the Craps game.                                                                                                          *
     *                                                                                                                                                                  *
     * This member function of the `Craps` class simulates the action of rolling two dice by generating random numbers for each die. The values for `Dice1` and         *
     * `Dice2` are set using a random number generator, with each dice value ranging from 1 to 6, inclusive.                                                            *
     *                                                                                                                                                                  *
     * @note This function is essential for the gameplay of Craps, as dice rolling is a fundamental aspect of the game.                                                 *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any game state other than the dice values.                                                    *
     *                                                                                                                                                                  *
     * @return void. This function does not return a value but updates the `Dice1` and `Dice2` member variables.                                                        *
     ********************************************************************************************************************************************************************/
    void RollDices();

    /********************************************************************************************************************************************************************
     * @brief Executes a round of Craps for a user.                                                                                                                     *
     *                                                                                                                                                                  *
     * This member function of the `Craps` class simulates a round of Craps for a user. The function starts by checking the user's monetary balance, and if the user    *
     * has no money, it manages their debt and attempts, and ends the game round. If the user has money, the function then checks for an automatic win based on a       *
     * predefined probability. If this condition is not met, the function proceeds to simulate the actual game by rolling dice and determining the outcome based on     *
     * Craps rules. Throughout the game, machine usage and temperature are updated, and the time spent by the user in the game is tracked.                              *
     *                                                                                                                                                                  *
     * @note This function is central to the Craps game, handling betting, dice rolling, and outcome determination.                                                     *
     *                                                                                                                                                                  *
     * @see User class for user-related operations.                                                                                                                     *
     * @see RollDices() for the dice rolling simulation.                                                                                                                *
     * @see getWinProbability() for determining the chance of an automatic win.                                                                                         *
     * @see getElapsedTime() for calculating the duration of the game round.                                                                                            *
     *                                                                                                                                                                  *
     * @param user Pointer to a `User` object representing the player.                                                                                                  *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions but relies on methods that might (e.g., user balance checks, dice rolling).                             *
     * @exceptsafe This function provides basic exception safety. If an exception is thrown, the user's state remains unchanged.                                        *
     *                                                                                                                                                                  *
     * @return bool - The outcome of the game: `true` if the user wins or the game round completes, `false` otherwise.                                                  *
     ********************************************************************************************************************************************************************/
    bool Play(User* user) override ;
};


#endif //CODE_CRAPS_H
