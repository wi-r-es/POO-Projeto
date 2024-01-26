//
// Created on 25/01/24.
//

#ifndef CODE_UTILS_H
#define CODE_UTILS_H

#include <utility>
#include <random>
#include <chrono>
#include <thread>

int randomNumberGeneratorInterval(int x, int y);
void Wait(int seconds);
std::chrono::seconds getElapsedTime(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);
#endif //CODE_UTILS_H
