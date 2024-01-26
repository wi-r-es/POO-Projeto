//
// Created on 06/11/23.
//


#include "Headers/User.h"


User::User(char *id, std::string name, std::string city, int age) : d_name(std::move(name)), d_city(std::move(city)), d_age(age){
    std::strcpy(d_id, id);
    d_money=0;
    d_time_spent=0;
    d_prizes_won=0;
    playing = 0;
    bets=0;
    profit=0;

}

User::~User(){

}

// Setters and Getters
const char *User::getId() const {
    return d_id;
}

const std::string &User::getName() const {
    return d_name;
}

void User::setName(const std::string &dName) {
    d_name = dName;
}

const std::string &User::getCity() const {
    return d_city;
}

void User::setCity(const std::string &dCity) {
    d_city = dCity;
}

int User::getAge() const {
    return d_age;
}

void User::setAge(int dAge) {
    d_age = dAge;
}

int User::getTimeSpent() const {
    return d_time_spent;
}

void User::setTimeSpent(int dTimeSpent) {
    d_time_spent = dTimeSpent;
}

int User::getPrizesWon() const {
    return d_prizes_won;
}

void User::setPrizesWon(int dPrizesWon) {
    d_prizes_won = dPrizesWon;
}

int User::getPlaying() const {
    return playing;
}

void User::setPlaying(int playing) {
    playing = 1;
}

float User::getMoney() const {
    return d_money;
}

void User::setMoney(float money) {
    d_money = money;
}


void User::addDebt(float amountOfDebt) {
    if( debt >= 1000 ){
        printf("TOO MANY DEBT. HOUSE GOT FORECLOSED . THIS CASINO WILL NO LONGER LEND MONEY TO THIS USER...\n\n ");
        return;}
    debt += amountOfDebt;
    this->setMoney(amountOfDebt);
}
float User::getDebt() const {
    return debt;
}

void User::incAttempts() {
    count_plays_no_money++;
}
int User::getAttempts()const {
    return count_plays_no_money;
}

void User::playGame(Machine* Mac){

}

void User::resetAttempts() {
    count_plays_no_money=0;
}

std::string User::toString() {

    return std::string();
}







