//
// Created on 25/01/24.
//

#include "Headers/utils.h"

int randomNumberGeneratorInterval(int x, int y) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(x, y);
    return distr(eng);
}

void Wait(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

/** Computates time passed **/
std::chrono::seconds getElapsedTime(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end){
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    return duration;
}

