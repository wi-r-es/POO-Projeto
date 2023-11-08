//
// Created on 06/11/23.
//

#include <utility>
#include "Headers/User.h"


User::User(char *id, std::string name, std::string city, int age) : d_name(std::move(name)), d_city(std::move(city)), d_age(age){
    std::strcpy(d_id, id);
    d_time_spent=0;
    d_prizes_won=0;
    playing=0;

}

User::~User(){

}

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
    User::playing = playing;
}


void User::playGame(Machine* Mac){

}