//
// Created on 25/01/24.
//

#ifndef CODE_UTILS_H
#define CODE_UTILS_H

#include <utility>
#include <random>
#include <chrono>
#include <thread>
#include <list>
#include <type_traits>

#include "Machine.h"

/*******************************************************************************************************************************************************************
 * @brief Generates a random number within a specified interval.
 *
 * This function generates and returns a random number within the interval [x, y], inclusive. It utilizes the <random> library to produce uniformly distributed
 * integers. The function creates a random device and a Mersenne Twister engine for generating high-quality random integers.
 *
 * @note This function is essential for scenarios requiring random number generation, such as simulations, games, or probabilistic calculations.
 *
 * @param x The lower bound of the interval (inclusive).
 * @param y The upper bound of the interval (inclusive).
 *
 * @exception None. This function does not throw exceptions.
 * @exceptsafe This function is exception-neutral and does not modify any program state.
 *
 * @return int - A random integer within the specified interval.
 *******************************************************************************************************************************************************************/
int randomNumberGeneratorInterval(int x, int y);

/*******************************************************************************************************************************************************************
 * @brief Pauses the execution of the current thread for a specified duration.
 *
 * This function suspends the execution of the current thread for a given number of seconds. It uses `std::this_thread::sleep_for` from the <chrono> library
 * to create the delay. This function is useful in scenarios where a time-controlled pause in execution is required, such as simulations or timed events.
 *
 * @note Useful for introducing delays or timing control in the program's execution flow.
 *
 * @param seconds The duration of the pause in seconds.
 *
 * @exception None. This function does not throw exceptions.
 * @exceptsafe This function is exception-neutral and does not modify any program state.
 *
 * @return void. This function does not return a value but causes the current thread to sleep.
 *******************************************************************************************************************************************************************/
void Wait(int seconds);

/*******************************************************************************************************************************************************************
 * @brief Calculates the elapsed time between two time points.
 *
 * This function computes the duration between two `std::chrono::steady_clock::time_point` instances. It returns the duration in seconds as a `std::chrono::seconds`
 * object. This function is particularly useful for measuring the time taken by a segment of code or the duration of an event in the application.
 *
 * @param start The starting time point.
 * @param end The ending time point.
 *
 * @exception None. This function does not throw exceptions.
 * @exceptsafe This function is exception-neutral and does not modify any program state.
 *
 * @return std::chrono::seconds - The duration between the start and end time points, expressed in seconds.
 *******************************************************************************************************************************************************************/
std::chrono::seconds getElapsedTime(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);



#endif //CODE_UTILS_H
