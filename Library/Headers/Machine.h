//
//  Edit comments in this sections

//
/**********************************************************************************
 *  @file Machine.h                                                               *
 *  @brief Class prototypes for Casino Machines ADT Structure/Class               *
 *                                                                                *
 *  This contains the prototypes for the managing of Machines and its fields.     *
 *                                                                                *
 **********************************************************************************/
#ifndef CODE_MACHINE_H
#define CODE_MACHINE_H

#include <iostream>
#include <string>
#include "Headers/User.h"
// Enumerations for machine type and state
// using class for scope restriction and unsigned char for memory optimization
enum class MACHINE_TYPE : unsigned char {CLASSIC_SLOT =1 ,          // 1
                                        THEMATIC_SLOT,              // 2
                                        FEATURE_SLOT,               // 3
                                        BLACKJACK,                  // 4
                                        ROULETTE,                   // 5
                                        CRAPS,                      // 6
                                        BACCARAT,                   // 7
                                        POKER};                     // 8


enum class MACHINE_STATE : unsigned char {OFF, ON, BROKEN}; // maybe add another value, TBD

// to use simply use MACHINE_TYPE::BLACKJACK for example


/**********************************************************************************************
 * Machine ADT class and vars description                                                     *
 * ID                       -> TYPE_TBD of the Unique identifier (ID) for each machine.       *
 * state                    -> Current state of the machine.                                  *
 * type                     -> Type of game the machine offers.                               *
 * failureProbability       -> Generic LL for all products ("database").                      *
 * temperature              -> Current temperature of the machine.                            *
 * posX,posY                -> Position of the machine in the casino (X, Y).                  *
 * winProbability           -> Probability that a user will win at this machine.              *
 * failures                 -> Number of times the machine has failed.                        *
 * usage                    -> Number of times the machine was used.                          *
 **********************************************************************************************/
class Machine {
private:
    int UID;
    MACHINE_TYPE TYPE;
    MACHINE_STATE state;
    float failureProbability;
    float temperature;
    int posX, posY;
    float winProbability;
    int failures;
    int usage;

public:
    /***********************************************************************
     * @brief Constructor for Machine                                      *
     *                                                                     *
     *        The UID of the machine is generated.                         *
     *                                                                     *
     * @param type  -> Enum type indicating the type of the Machine.       *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    Machine(MACHINE_TYPE type, int posX, int posY);  // id =  idtype seguido de um numero [WIP]
    /***********************************
     * @brief Destructor for Machine   *
     ***********************************/
    virtual ~Machine();

    /***********************************************
     * @brief Getter for the UID of the Machine    *
     * @return The UID of the machine.             *
     ***********************************************/
    int getUID() const;

    /*********************************************************************
     * @brief Getter for the number of the times the Machine was used    *
     * @return The Number of usages.                                     *
     *********************************************************************/
    int getUsage() const;

    /************************************************************
     * @brief Increments the number of times a machine was used *
     ************************************************************/
    void incUsage();

    /*****************************************************************************************
     * @brief Getter for the current state of the Machine                                    *
     * @return The current Machine State. One of the following options: OFF, ON or BROKEN.   *
     *****************************************************************************************/
    MACHINE_STATE getState();

    /****************************************************************************************
     * @brief Setter for the current state of the Machine                                   *
     *                                                                                      *
     * @param newState -> MACHINE_STATE enum indicating the current state of the machine.   *
     ****************************************************************************************/
    void setState(MACHINE_STATE newState);

    /****************************************************
     * @brief Getter for Machine Position               *
     * @return a pair of the position of the machine.   *
     ****************************************************/
    std::pair<int, int> getPosition();

    /***********************************************************************
     * @brief Setter for Machine Position                                  *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     ***********************************************************************/
    void setPosition(int newX, int newY);

    /************************************************
     * @brief Getter for Machine win probability    *
     * @return Float representing Win probability.  *
     ************************************************/
    float getWinProbability() const;

    /**********************************************************
     * @brief Setter for Machine win probability              *
     * @param newProb -> Float representing Win probability.  *
     **********************************************************/
    void setWinProbability(float newProb);

    /*******************************************************
     * @brief Getter for Machine Number of failures        *
     * @return Integer representing number of failures.    *
     *******************************************************/
    int getFailures() const;

    /***************************************************************************
     * @brief Function to increment the number of times a machine has failed.  *
     ***************************************************************************/
    void incrementFailures();

    /******************************************
     * @brief Getter for Machine Temperature  *
     * @return Machine Temperature            *
     ******************************************/
    float getTemperature() const;

    /*******************************************************
     * @brief Setter for the Machine current temperature   *
     * @param newTemp                                      *
     ******************************************************/
    void setTemperature(float newTemp);

    /**********************************************************************************
     * @brief Function that simulates the operation of the Machine .                  *
     *                                                                                *
     **********************************************************************************/
    virtual void Play(User* user);
};



#endif //CODE_MACHINE_H
