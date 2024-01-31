//
// Created on 06/11/23.
//


#include <utility>

#include "Headers/User.h"


User::User(char *id, std::string name, std::string city, int age) : d_name(std::move(name)), d_city(std::move(city)), d_age(age){
    std::strcpy(d_id, id);
    d_money=0;
    d_prizes_won=0;
    playing = 0;
    d_bets=0;
    //d_profit=0;
}

User::~User(){
}

// Setters and Getters
const char *User::getId() const {
    return d_id;
}


void User::setName(const std::string &dName) {
    d_name = dName;
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

long User::getTimeSpent() const {
    return d_time_spent.count();
}

void User::incTimeSpent(std::chrono::seconds dTimeSpent) {
    d_time_spent += dTimeSpent;
}

float User::getPrizesWon() const {
    return d_prizes_won;
}

void User::incPrizesWon(float dPrizesWon) {
    d_prizes_won += dPrizesWon;
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
    if( d_debt >= 1000 ){
        printf("TOO MANY DEBT. HOUSE GOT FORECLOSED . THIS CASINO WILL NO LONGER LEND MONEY TO THIS USER...\n\n ");
        return;}
    d_debt += amountOfDebt;
    this->setMoney(amountOfDebt);
}
float User::getDebt() const {
    return d_debt;
}

void User::incAttempts() {
    count_plays_no_money++;
}
int User::getAttempts()const {
    return count_plays_no_money;
}


void User::resetAttempts() {
    count_plays_no_money=0;
}

std::string User::toString() {

    std::string s;

    s.append("[ID]->").append(d_id).append(";");
    //s.append(" [Name]->").append(*d_name).append(";");
    //s.append(" [City]->").append(*d_city).append(";");
    s.append(" [Age]->").append(std::to_string(d_age)).append(";");
    s.append(" [Time Spent]->").append(std::to_string(getTimeSpent())).append(";");
    s.append(" [Prizes Won]->").append(std::to_string(d_prizes_won)).append(";");
    s.append(" [Playing]->").append(playing ? "Yes" : "No").append(";");
    s.append(" [Money]->").append(std::to_string(d_money)).append(";");
    s.append(" [Bets]->").append(std::to_string(d_bets)).append(";");
    s.append(" [Debt]->").append(std::to_string(d_debt)).append(";");
    s.append(" [Attempts No Money]->").append(std::to_string(count_plays_no_money));

    return s;
}

const std::string &User::getName() const {
    return d_name;
}

const std::string &User::getCity() const {
    return d_city;
}

int User::getBets() const {
    return d_bets;
}

void User::incBets(int bets) {
    d_bets += bets;
}







