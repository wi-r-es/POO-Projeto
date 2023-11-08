//
// Created on 06/11/23.
//

#include <utility>

#include "Headers/User.h"


User::User(char *id, std::string name, std::string city, int age) : d_name(std::move(name)), d_city(std::move(city)), d_age(age){
    d_id;
    d_time_spent=0;
    d_prizes_won=0;
    playing=0;

}
User::~User(){

}

void User::playGame(){

}