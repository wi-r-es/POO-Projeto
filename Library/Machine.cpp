//
// Created on 06/11/23.
//

#include "Headers/Machine.h"

Machine::Machine(MACHINE_TYPE type, int posX, int posY) : TYPE(type), posX(posX), posY(posY) {
    static short int serialNumber = 1; // Static variable to keep track of the last used number
    UID = serialNumber++; // probably will be changed, not a problem for now ig?
    state = OFF;
    failureProbability = 0.3; // <=> 30%
    temperature = 25.0;
    winProbability = 0.1; // <=> 10%
    failures = 0;
    usage=0;
}

Machine::~Machine(){

}

int Machine::getUID() const{
    return UID;
}

int Machine::getUsage() const{
    return usage;
}
void Machine::incUsage(){
    usage++;
}

MACHINE_STATE Machine::getState() {
    return state;
}

void Machine::setState(MACHINE_STATE newState) {
    state = newState;
}

std::pair<int, int> Machine::getPosition() {
    return std::make_pair(posX, posY);
}

void Machine::setPosition(int newX, int newY) {
    posX = newX;
    posY = newY;
}

float Machine::getWinProbability() const {
    return winProbability;
}

void Machine::setWinProbability(float newProb) {
    if (newProb >= 0.0f && newProb <= 1.0f) {
        winProbability = newProb;
    }
}

int Machine::getFailures() const {
    return failures;
}

void Machine::incrementFailures() {
    failures++;
}

float Machine::getTemperature() const {
    return temperature;
}

void Machine::setTemperature(float newTemp) {
    if (newTemp >= 0.0f) {
        temperature = newTemp;
    }
}
void Machine::Play(User* user){
    std::cout << __FUNCTION__  << std::endl;
}