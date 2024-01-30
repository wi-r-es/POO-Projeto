//
// Created on 18/11/23.
//

#ifndef CODE_IO_H
#define CODE_IO_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

#include "Machine.h"
using namespace std;


/*******************************************************************************************************************************************************************
 * @brief Logs execution details to a file.
 *
 * This function logs specific information about the execution of a function to a given file. It records the date, time, function name, and a brief description
 * of the execution context or any pertinent information. The log entry is appended to the specified file. If the file cannot be opened, an error is reported.
 *
 * @note This function is essential for debugging and tracking the execution flow of the program.
 *
 * @param filename The name of the file where the log will be recorded.
 * @param funcname The name of the function being logged.
 * @param info A brief description of the context or information related to the function execution.
 *
 * @exception std::runtime_error Thrown if the file cannot be opened.
 * @exceptsafe This function provides strong exception safety. If an exception is thrown, no change is made to the program's state.
 *
 * @return void. This function does not return a value but writes to an output file.
 *******************************************************************************************************************************************************************/
void logging(const std::string& filename, const std::string& funcname, const std::string& info);

/*******************************************************************************************************************************************************************
 * @brief Outputs a formatted string with a decorative border.
 *
 * This function formats a given string with a decorative border made of a specified character. The string is centered, and the total width of the formatted
 * output is set to a fixed width (50 characters). This function is primarily used for enhancing the readability and presentation of console outputs.
 *
 * @note Useful for displaying titles, headers, or important notices in a visually appealing format.
 *
 * @param str The string to be formatted.
 * @param ch The character used to create the border.
 *
 * @exception None. This function does not throw exceptions.
 * @exceptsafe This function is exception-neutral and does not modify any program state.
 *
 * @return void. This function does not return a value but outputs to the standard console.
 *******************************************************************************************************************************************************************/
void beautify(const std::string& str, char ch = '#');

/*******************************************************************************************************************************************************************
 * @brief Displays the given time in a human-readable format.
 *
 * This function takes a `time_t` object and prints it to the console in a human-readable format. The time is formatted according to the `asctime` function,
 * which typically represents the time in a 'Day Month Date Hours:Minutes:Seconds Year' format.
 *
 * @note This function is useful for displaying timestamps or time-related information to the user.
 *
 * @param _time The `time_t` object representing the time to be displayed.
 *
 * @exception None. This function does not throw exceptions.
 * @exceptsafe This function is exception-neutral and does not modify any program state.
 *
 * @return void. This function does not return a value but outputs to the standard console.
 *******************************************************************************************************************************************************************/
void printTime(const time_t& _time);

/*******************************************************************************************************************************************************************
 * @brief Lists and copies machines from a vector to a list.
 *
 * This function iterates through a vector of `Machine` pointers, outputs their string representation to a provided output stream, and copies them into a list.
 * This is particularly useful for transferring or displaying machine data from one container type to another.
 *
 * @note Useful for operations that involve processing or displaying a collection of `Machine` objects.
 *
 * @param container A constant reference to a vector containing `Machine` pointers.
 * @param l A reference to a list where `Machine` pointers will be copied.
 * @param f A reference to an output stream where the machine details will be written.
 *
 * @exception None. This function does not throw exceptions.
 * @exceptsafe This function is exception-neutral and does not modify any program state.
 *
 * @return void. This function does not return a value but outputs to the standard console.
 *******************************************************************************************************************************************************************/
void List_Specific_Containers(const std::vector<Machine *>& container, std::list<Machine *> &l,std::ostream &f = std::cout);


#endif //CODE_IO_H
