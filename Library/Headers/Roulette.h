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

#include <list>

#include <utility>
using namespace std;

#include "Machine.h"
#include "User.h"


/************************************************************************************************
 * Roulette ADT class description derived from Machine                                          *
 *                                                                                              *
 * Inherits from Machine class. Represents a Roulette game machine typically found in casinos.  *
 * The Roulette class encompasses attributes and mechanisms specific to this game.              *
 *                                                                                              *
 * BOARD                  -> A map associating each number on the Roulette wheel with its       *
 *                           corresponding color ('red' or 'black', with the exception of '0'   *
 *                           and '00' which are typically green). This is essential for         *
 *                           determining winning bets based on color.                           *
 *                                                                                              *
 * colorbet               -> A map for tracking color bets placed by players. The key is an     *
 *                           integer representing the bet amount, and the value is a string     *
 *                           indicating the color bet on ('red' or 'black'). This facilitates   *
 *                           the management of color-based bets and payouts.                    *
 *                                                                                              *
 * The class would likely include methods for simulating the spinning of the Roulette wheel,    *
 * handling bets, and determining winning numbers and colors. These methods would utilize       *
 * both the inherited attributes from the Machine class and the specific attributes of the      *
 * Roulette class.                                                                              *
 ************************************************************************************************/
class Roulette : public Machine {
private:
    map<int, string> BOARD;

    map<int, string> colorbet;

public:

    /*******************************************************************************************************************************************************************
     * @brief Constructor for Roulette with specified position parameters.
     *
     * This constructor initializes an instance of the `Roulette` class, which is derived from the `Machine` class. It sets the machine's type to `ROULETTE` and
     * initializes its position to the provided coordinates (`posX`, `posY`). Additionally, it initializes the Roulette board with predefined black, red, and green
     * numbers, following standard Roulette rules.
     *
     * @param posX The x-coordinate of the Roulette table's position.
     * @param posY The y-coordinate of the Roulette table's position.
     *
     * @exception None. This constructor does not throw exceptions.
     * @exceptsafe This constructor is exception-neutral and offers no guarantees if an exception is thrown during initialization.
     *
     * @return None. Constructors do not return values.
     *******************************************************************************************************************************************************************/
    Roulette(int posX, int posY);

    /*******************************************************************************************************************************************************************
     * @brief Default Constructor for Roulette.
     *
     * This default constructor initializes an instance of the `Roulette` class with default position values (0, 0) and sets the machine type to `ROULETTE`. It also
     * initializes the Roulette board similarly to the overloaded constructor. This constructor is used when no specific position is provided for the Roulette table.
     *
     * @note This constructor provides a way to create a Roulette table with default settings. Mostly for testing purposes.
     *
     * @exception None. This constructor does not throw exceptions.
     * @exceptsafe This constructor is exception-neutral and offers no guarantees if an exception is thrown during initialization.
     *
     * @return None. Constructors do not return values.
     *******************************************************************************************************************************************************************/
    Roulette();

    /*********************************************
     * @brief Destructor for Roulette Machine    *
     *********************************************/
    virtual ~Roulette();


    /*******************************************************************************************************************************************************************
     * @brief Prints the Roulette board mapping.
     *
     * This member function of the `Roulette` class outputs the current state of the Roulette board to the console. It displays each number and its corresponding
     * color (black, red, or green) as per the Roulette rules. This function was primarily used for debugging purposes.
     *
     * @note This function can be used to verify the correct initialization and state of the Roulette board. For testing purposes.
     *
     * @exception None. This function does not throw exceptions.
     * @exceptsafe This function is exception-neutral and does not modify any game state.
     *
     * @return void. This function does not return a value but outputs the board state to the standard output.
     *******************************************************************************************************************************************************************/
    void printMap() const;


    /*******************************************************************************************************************************************************************
     * @brief Generates a winning number and color for a Roulette spin.
     *
     * This member function simulates the spinning of the Roulette wheel by generating a random winning number and determining its corresponding color. It returns
     * both the winning number and its color, which are essential for determining the outcome of a bet.
     *
     * @note This function is crucial for simulating the outcome of a Roulette spin.
     *
     * @exception None. This function does not throw exceptions but relies on the randomNumberGeneratorInterval function.
     * @exceptsafe This function is exception-neutral and does not modify any game state.
     *
     * @return pair<int, string> - A pair containing the winning number and its corresponding color.
     *******************************************************************************************************************************************************************/
    pair<int, string> oddGenerate();

    /*******************************************************************************************************************************************************************
     * @brief Simulates a single color bet in Roulette.
     *
     * This member function simulates placing a bet on a color in the Roulette game. It randomly selects between the two colors (black or red) and returns the
     * selected color. This function is used in the `Play` function to simulate the user's bet.
     *
     * @note This function is used for simulating a color bet in the game of Roulette.
     *
     * @exception None. This function does not throw exceptions but relies on the randomNumberGeneratorInterval function.
     * @exceptsafe This function is exception-neutral and does not modify any game state.
     *
     * @return string - The color on which the bet is placed.
     *******************************************************************************************************************************************************************/
    string simulate_singlebet();

    /*******************************************************************************************************************************************************************
     * @brief Executes a round of Roulette for a user.
     *
     * This member function of the `Roulette` class simulates a round of Roulette for a user. It checks the user's monetary balance and manages their betting
     * process. The function simulates the user placing a bet, spinning the Roulette wheel, and determines the outcome based on the generated winning number and
     * color. It updates the user's balance based on the outcome, and machine statistics such as usage and temperature are adjusted accordingly.
     *
     * @note This function integrates user interaction with the Roulette game, handling the betting process, spin simulation, and outcome determination.
     *
     * @see User class for user-related operations.
     * @see oddGenerate() for simulating the Roulette spin.
     * @see getWinProbability() for determining the chance of an automatic win.
     * @see getElapsedTime() for calculating the duration of the game round.
     *
     * @param user Pointer to a `User` object representing the player.
     *
     * @exception None. This function does not throw exceptions but relies on methods that might (e.g., user balance checks, bet simulation).
     * @exceptsafe This function provides basic exception safety. If an exception is thrown, the user's state remains unchanged.
     *
     * @return bool - The outcome of the game: `true` if the user wins or the game round completes, `false` otherwise.
     *******************************************************************************************************************************************************************/
    bool Play(User* user) override ;
};



#endif //CODE_ROULETTE_H
