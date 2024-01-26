//
// Created on 06/11/23.
//

#include "Headers/Machine.h"

Machine::Machine(MACHINE_TYPE type, int posX, int posY) : TYPE(type), posX(posX), posY(posY) {
    static short int serialNumber = 1; // Static variable to keep track of the last used number
    UID = serialNumber++; // probably will be changed, not a problem for now ig?
    state = MACHINE_STATE::ON;
    failureProbability = 0.3; // <=> 30%
    temperature = 18.0;
    winProbability = 0.1; // <=> 10%
    failures = 0;
    usage=0;
    betAmount=0;
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

MACHINE_TYPE Machine::getType() {
    return TYPE;
}

void Machine::setState(MACHINE_STATE newState) {
    state = newState;
}

std::pair<int, int> Machine::getPosition() {
    return std::make_pair(posX, posY);
}

void Machine::setFailureProbability(float prob) {
    failureProbability = prob;
}

float Machine::getFailureProbability() const{
    return failureProbability;
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
void Machine::increaseTemperature() {
    temperature+=0.5f;
}

void Machine::setTemperature(float newTemp) {
    if (newTemp >= 0.0f) {
        temperature = newTemp;
    }
}
void Machine::setBetAmount(float bet) {
    Machine::betAmount = bet;
    std::cout << "Money withdrawn from user to bet: " << bet << std::endl;
}
float Machine::getBetAmount() const {
    return betAmount;
}

int Machine::randomNumberGeneratorInterval(int x, int y) {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(x, y); // Define the range

    int randomValue = distr(eng); // Generate a random number within the range
    return randomValue;
}


bool Machine::Play(User* user){
    std::cout << __FUNCTION__  << std::endl;
}

std::string Machine::toString() const{
    std::string s = "[ID]->" + std::to_string(UID);  s.append(";");
    s.append(" [TYPE]->" + std::to_string(static_cast<int>(TYPE))); s.append(";");
    s.append("\t\t[STATE]->" + machineSTATEToString(state)); s.append(";");
    s.append("[TEMPERATURE]->" + std::to_string(temperature)); s.append(";");
    s.append("[X,Y]->" + std::to_string(posX) + "," + std::to_string(posY)); s.append(";");
    s.append("[winProbability]->" + std::to_string(winProbability)); s.append(";");
    s.append("[Failures]->" + std::to_string(failures)); s.append(";");
    s.append("[betAmount]->" + std::to_string(betAmount)); s.append(";");
    s.append("[usage]->" + std::to_string(usage));
    return s;
}

std::string Machine::toStringOut() const{
    std::string s = "\t[ID]->" + std::to_string(UID);  s.append("\n");
    s.append("\t\t[TYPE]->" + machineTypeToString(TYPE)); s.append("\n");
    s.append("\t\t[STATE]->" + machineSTATEToString(state)); s.append("\n");
    s.append("\t\t[TEMPERATURE]->" + std::to_string(temperature)); s.append("\n");
    s.append("\t\t[X,Y]->" + std::to_string(posX) + "," + std::to_string(posY)); s.append("\n");
    s.append("\t\t[winProbability]->" + std::to_string(winProbability)); s.append("\n");
    s.append("\t\t[Failures]->" + std::to_string(failures)); s.append("\n");
    s.append("\t\t[betAmount]->" + std::to_string(betAmount)); s.append("\n");
    s.append("\t\t[usage]->" + std::to_string(usage)); s.append("\n");
    return s;
}

std::chrono::steady_clock::time_point Machine::getTimeInMaintenance() {
    return coolingtime;
}

void Machine::setMaintenanceTime(std::chrono::steady_clock::time_point time) {
    coolingtime = time;
}

void Machine::reset() {
    failureProbability = 0.3;
    temperature = 18.0;
    winProbability = 0.1;
}

std::string machineTypeToString(MACHINE_TYPE type) {
    switch (type) {
        case MACHINE_TYPE::CLASSIC_SLOT: return "CLASSIC_SLOT";
        case MACHINE_TYPE::THEMATIC_SLOT: return "THEMATIC_SLOT";
        case MACHINE_TYPE::FEATURE_SLOT: return "FEATURE_SLOT";
        case MACHINE_TYPE::BLACKJACK: return "BLACKJACK";
        case MACHINE_TYPE::ROULETTE: return "ROULETTE";
        case MACHINE_TYPE::CRAPS: return "CRAPS";
        case MACHINE_TYPE::BACCARAT: return "BACCARAT";
        case MACHINE_TYPE::POKER: return "POKER";
        default: return "UNKNOWN_TYPE";
    }
}std::string machineSTATEToString(MACHINE_STATE state) {
    switch (state) {
        case MACHINE_STATE::MAINTENANCE : return "MAINTENANCE";
        case MACHINE_STATE::OFF: return "OFF";
        case MACHINE_STATE::ON: return "ON";
        case MACHINE_STATE::NONEXISTENT : return "NONEXISTENT";
        case MACHINE_STATE::BROKEN: return "BROKEN";
        default: return "UNKNOWN_TYPE";
    }
}


