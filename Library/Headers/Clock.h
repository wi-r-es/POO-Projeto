//
// Created on 25/01/24.
//
/**********************************************************************************
 *  @file Clock.h                                                                 *
 *  @brief Class prototypes for Casino Clock ADT Structure/Class                  *
 *                                                                                *
 *  This contains the prototypes for the managing of Clock and its fields.        *
 *  It is an C++ adaptation of the previously given Clock struct in ED UC         *
 *                                                                                *
 **********************************************************************************/
#ifndef CODE_CLOCK_H
#define CODE_CLOCK_H

#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
/**********************************************************************************************
 * Clock ADT class description                                                                *
 *                                                                                            *
 * The Clock class is designed to manage time-related functionalities within the application. *
 * It is not inheriting from any other class and serves as a standalone entity for time       *
 * management. The class encapsulates time management mechanisms, allowing for the            *
 * simulation of time flow or tracking of real-world time.                                    *
 *                                                                                            *
 * START         -> An instance of time_t representing the start point of the clock.          *
 *                  This could be the time when the Clock object is instantiated or another   *
 *                  predefined time. It serves as a reference point for all time calculations.*
 *                                                                                            *
 * SPEED         -> An integer representing the speed factor of the clock. A value of 1       *
 *                  would typically mean real-time progression, while higher values indicate  *
 *                  an accelerated time flow. This is particularly useful in simulations or   *
 *                  scenarios where time needs to be manipulated or observed at different     *
 *                  speeds.                                                                   *
 *                                                                                            *
 * START_TIME    -> Another instance of time_t,  used to store the actual real-world          *
 *                  starting time when the clock was set. This could be used for              *
 *                  logging, debugging, or synchronizing with real-world time events.         *
 *                                                                                            *
 **********************************************************************************************/
class Clock {
private:
    time_t START{};
    int SPEED{};
    time_t START_TIME{};
public:

    /********************************************************************************************************************************************************************
     * @brief Default Constructor for Clock.                                                                                                                            *
     *                                                                                                                                                                  *
     * This constructor initializes a `Clock` instance with default settings. It sets the initial starting time (`START`) to the current time, speed (`SPEED`) to 0,    *
     * and the software start time (`START_TIME`) to an empty struct. This setup is suitable for scenarios where specific clock settings are not required initially.    *
     *                                                                                                                                                                  *
     * @note This constructor is used for initializing the clock with default settings.                                                                                 *
     *                                                                                                                                                                  *
     * @exception None. This constructor does not throw exceptions.                                                                                                     *
     * @exceptsafe This constructor is exception-neutral.                                                                                                               *
     *                                                                                                                                                                  *
     * @return None. Constructors do not return values.                                                                                                                 *
     ********************************************************************************************************************************************************************/
    Clock();

    /********************************************************************************************************************************************************************
     * @brief Parameterized Constructor for Clock.                                                                                                                      *
     *                                                                                                                                                                  *
     * This constructor initializes a `Clock` instance with specified settings. It allows setting the initial start time (`START`), speed of time flow (`SPEED`),       *
     * and the software-based start time (`START_TIME`). This setup is useful for simulations that require a specific start time and time flow rate.                    *
     *                                                                                                                                                                  *
     * @param start The initial hardware-based start time.                                                                                                              *
     * @param velocity The speed at which time progresses in the simulation.                                                                                            *
     * @param start_time The software-based start time.                                                                                                                 *
     *                                                                                                                                                                  *
     * @note This constructor provides flexibility for initializing the clock with custom settings.                                                                     *
     *                                                                                                                                                                  *
     * @exception None. This constructor does not throw exceptions.                                                                                                     *
     * @exceptsafe This constructor is exception-neutral.                                                                                                               *
     *                                                                                                                                                                  *
     * @return None. Constructors do not return values.                                                                                                                 *
     ********************************************************************************************************************************************************************/
    Clock(time_t start, int speed, time_t horaInicio);

    /*********************************
     * @brief Destructor for Clock   *
     *********************************/
    ~Clock();

    /********************************************************************************************************************************************************************
     * @brief Starts the clock with a specified speed and start time.                                                                                                   *
     *                                                                                                                                                                  *
     * This member function sets the `Clock` instance's starting time to the current time, adjusts the speed, and initializes the software-based start time based on    *
     * the given string. It is used to configure the clock's operational parameters and to begin time progression in the simulation.                                    *
     *                                                                                                                                                                  *
     * @param speed The speed at which time should progress.                                                                                                            *
     * @param start_time A string representing the start time (formatted as "HH:MM:SS").                                                                                *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions but relies on standard library functions that may set `errno`.                                          *
     * @exceptsafe This function is exception-neutral and does not modify any game state other than the clock settings.                                                 *
     *                                                                                                                                                                  *
     * @return void. This function does not return a value.                                                                                                             *
     *******************************************************************************************************************************************************************/
    void StartClock(int speed, const std::string& H_Inicio);

    /********************************************************************************************************************************************************************
     * @brief Gets the current simulated time.                                                                                                                          *
     *                                                                                                                                                                  *
     * This member function calculates and returns the current simulated time based on the initial start time, the elapsed real time, and the speed of the clock.       *
     * It is essential for retrieving the current time in the context of the simulation.                                                                                *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any game state.                                                                               *
     *                                                                                                                                                                  *
     * @return time_t - The current simulated time.                                                                                                                     *
     ********************************************************************************************************************************************************************/
    [[nodiscard]] time_t getTime() const;

    /***************************************************
     * @brief Converts a clock object into a string    *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return a String representation of the object   *
     ***************************************************/
    [[nodiscard]] std::string toString() const;

    /*******************************************************************
     * @brief Converts a clock object into a string meant for output   *
     * @exceptsafe none - Shall not throw exceptions                   *
     * @return a String representation of the object                   *
     *******************************************************************/
    [[maybe_unused]] std::string toStringOut() const;
};




#endif //CODE_CLOCK_H
