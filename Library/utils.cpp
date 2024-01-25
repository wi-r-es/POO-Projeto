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

