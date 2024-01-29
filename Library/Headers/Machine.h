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
#include <map>
#include <string>
#include <vector>
#include <random>
#include <chrono>


#include "utils.h"
#include "User.h"

/*********************************************************************************
 * Enumerations for machine type for extra support to the Machine Class          *
 * Using class for scope restriction and unsigned char for memory optimization   *
 *********************************************************************************/
enum class MACHINE_TYPE : unsigned char {CLASSIC_SLOT =1 ,          // 1
                                        THEMATIC_SLOT,              // 2
                                        FEATURE_SLOT,               // 3
                                        BLACKJACK,                  // 4
                                        ROULETTE,                   // 5
                                        CRAPS,                      // 6
                                        BACCARAT,                   // 7
                                        POKER};                     // 8

std::string machineTypeToString(MACHINE_TYPE type);

/*********************************************************************************
 * Enumerations for machine state for extra support to the Machine Class         *
 * Using class for scope restriction and unsigned char for memory optimization   *
 *********************************************************************************/
enum class MACHINE_STATE : unsigned char {OFF, ON, BROKEN, MAINTENANCE, NONEXISTENT};
std::string machineSTATEToString(MACHINE_STATE state);


/**********************************************************************************************
 * Machine ADT class description                                                              *
 *                                                                                            *
 * ID                       -> TYPE_TBD of the Unique identifier (ID) for each machine.       *
 * state                    -> Current state of the machine.                                  *
 * type                     -> Type of game the machine offers.                               *
 * failureProbability       -> Generic LL for all products ("database").                      *
 * temperature              -> Current temperature of the machine.                            *
 * posX,posY                -> Position of the machine in the casino (X, Y).                  *
 * winProbability           -> Probability that a user will win at this machine.              *
 * failures                 -> Number of times the machine has failed.                        *
 * betAmount                -> the bet amount of the round.                                   *
 * usage                    -> Number of times the machine was used.                          *
 * coolingtime              -> Time point object to simulate the machine getting fixed.       *
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
    float betAmount;
    int usage;
    std::chrono::steady_clock::time_point coolingtime;

public:

    /***********************************************************************
     * @brief Constructor for Machine                                      *
     *                                                                     *
     *        The UID of the machine is generated.                         *
     *                                                                     *
     * @exceptsafe none - Shall not throw exceptions                       *
     * @param type  -> Enum type indicating the type of the Machine.       *
     * @param posX  -> X Position of the machine in the casino (X, Y).     *
     * @param posY  -> Y Position of the machine in the casino (X, Y).     *
     * @return Newly created Machine object                                *
     ***********************************************************************/
    Machine(MACHINE_TYPE type, int posX, int posY);

    // id =  idtype seguido de um numero [WIP]
    /**************************************************
     * @brief Destructor for Machine                  *
     * @exceptsafe none - Shall not throw exceptions  *
     **************************************************/
    virtual ~Machine();

    /**************************************************
     * @brief Getter for the UID of the Machine       *
     * @exceptsafe none - Shall not throw exceptions  *
     * @return The UID of the machine.                *
     **************************************************/
    [[nodiscard]] int getUID() const;

    /*********************************************************************
     * @brief Getter for the number of the times the Machine was used    *
     * @exceptsafe none - Shall not throw exceptions                     *
     * @return The Number of usages.                                     *
     *********************************************************************/
    [[nodiscard]] int getUsage() const;

    /************************************************************
     * @brief Increments the number of times a machine was used *
     * @exceptsafe none - Shall not throw exceptions            *
     * @return None                                             *
     ************************************************************/
    void incUsage();

    /*****************************************************************************************
     * @brief Getter for the current state of the Machine                                    *
     * @exceptsafe none - Shall not throw exceptions                                         *
     * @return The current MACHINE_STATE. One of the following options: OFF, ON or BROKEN.   *
     *****************************************************************************************/
    MACHINE_STATE getState();

   /*********************************************************
    * @brief Getter for the current type of the Machine     *
    * @exceptsafe none - Shall not throw exceptions         *
    * @return The current Machine type. One of the games    *
    *********************************************************/
    MACHINE_TYPE getType();

    /****************************************************************************************
     * @brief Setter for the current state of the Machine                                   *
     * @exceptsafe none - Shall not throw exceptions                                        *
     * @param newState -> MACHINE_STATE enum indicating the current state of the machine.   *
     * @return None                                                                         *
     ****************************************************************************************/
    void setState(MACHINE_STATE newState);

    /****************************************************
     * @brief Getter for Machine Position               *
     * @exceptsafe none - Shall not throw exceptions    *
     * @return a pair of the position of the machine.   *
     ****************************************************/
    std::pair<int, int> getPosition();

    /***************************************************
     * @brief Setter for Machine Error Probability     *
     * @param prob of the machine to fail              *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return None                                    *
     ***************************************************/
    void setFailureProbability(float prob);

    /***************************************************
     * @brief Getter for Machine Error Probability     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return None                                    *
     ***************************************************/
    [[nodiscard]] float getFailureProbability() const;

    /***************************************************
     * @brief Getter for Machine win probability       *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return Win probability of the machine.         *
     ***************************************************/
    [[nodiscard]] float getWinProbability() const;

    /**********************************************************
     * @brief Setter for Machine win probability              *
     * @exceptsafe none - Shall not throw exceptions          *
     * @param newProb -> Float representing Win probability.  *
     * @return None                                           *
     **********************************************************/
    void setWinProbability(float newProb);

    /*******************************************************
     * @brief Getter for Machine Number of failures        *
     * @exceptsafe none - Shall not throw exceptions       *
     * @return Number of failures.                         *
     *******************************************************/
    [[nodiscard]] int getFailures() const;

    /***************************************************************************
     * @brief Function to increment the number of times a machine has failed.  *
     * @exceptsafe none - Shall not throw exceptions                           *
     * @return none                                                            *
     ***************************************************************************/
    void incrementFailures();

    /***************************************************
     * @brief Getter for Machine Temperature           *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return Machine Temperature                     *
     ***************************************************/
    [[nodiscard]] float getTemperature() const;

    /*******************************************************
     * @brief Setter for the Machine current temperature   *
     * @exceptsafe none - Shall not throw exceptions       *
     * @param newTemp new temperature for the machine      *
     * @return None                                        *
     *******************************************************/
    void setTemperature(float newTemp);

    /*******************************************************
     * @brief Increases the temperature of the machine     *
     * @exceptsafe none - Shall not throw exceptions       *
     * @return None                                        *
     *******************************************************/
    void increaseTemperature();

    /*******************************************************
     * @brief Setter for the bet amount of the machine     *
     * @exceptsafe none - Shall not throw exceptions       *
     * @param bet amount of the bet put into the round     *
     * @return None                                        *
     *******************************************************/
    virtual void setBetAmount(float bet);

    /********************************************************************
     * @brief Getter for the bet amount of the round in the machine     *
     * @exceptsafe none - Shall not throw exceptions                    *
     * @return None                                                     *
     ********************************************************************/
    [[nodiscard]] float getBetAmount() const;

    /*****************************************************************
     * @brief Random number generator between a min and a max        *
     * @exceptsafe none - Shall not throw exceptions                 *
     * @param x minimum number                                       *
     * @param y maximum number                                       *
     * @return Randomly generated integer between the given interval *
     *****************************************************************/
    int randomNumberGeneratorInterval(int x, int y);

    /************************************************************************
     * @brief Function that simulates the usage of the Machine by the user. *
     ************************************************************************/
    virtual bool Play(User* user);

    /***************************************************
     * @brief Converts a machine object into a string  *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return a String representation of the object   *
     ***************************************************/
    [[nodiscard]] std::string toString() const;

    /*******************************************************************
     * @brief Converts a machine object into a string meant for output *
     * @exceptsafe none - Shall not throw exceptions                   *
     * @return a String representation of the object                   *
     *******************************************************************/
    [[nodiscard]] std::string toStringOut() const;

    /*****************************************************************************
     * @brief Setter of the maintenance time point of machine object             *
     * @exceptsafe none - Shall not throw exceptions                             *
     * @param time time_point representing when the machine started maintenance  *
     * @return a String representation of the object                             *
     *****************************************************************************/
    void setMaintenanceTime(std::chrono::steady_clock::time_point time);

    /*********************************************************************************
     * @brief Getter of the maintenance time point of machine object                 *
     * @exceptsafe none - Shall not throw exceptions                                 *
     * @return a time_point value representing when the machine entered maintenance  *
     *********************************************************************************/
    std::chrono::steady_clock::time_point getTimeInMaintenance();

    /*****************************************************************************
     * @brief Function that resets the machine probabilities and temperature     *
     * @exceptsafe none - Shall not throw exceptions                             *
     * @return None                                                              *
     *****************************************************************************/
    void reset();

};



#endif //CODE_MACHINE_H
