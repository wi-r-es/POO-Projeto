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

class Clock {
private:
    time_t START{};
    int VELOCIDADE{};
    time_t Hora_Inicio{};
public:


    Clock();
    Clock(time_t start, int velocidade, time_t horaInicio);
    ~Clock();
    void StartClock(int Vel, const std::string& H_Inicio);
    time_t getTime() const;
    std::string toString() const;
};
#endif //CODE_CLOCK_H
