//
// Created on 06/11/23.
//

#include <utility>

#include "Headers/Casino.h"

Casino::Casino(std::string name): NAME(std::move(name)){

}

Casino::~Casino(){

}

bool Casino::Load(const std::string &file){

}
bool Casino::Add(User *usr){

}
bool Casino::Add(Machine *m){

}
void Casino::Listing(std::ostream &f){

}

void Casino::Listing(float X, std::ostream &f){

}

void Casino::TurnOff(int id_mac){

}
MACHINE_STATE Casino::getState(int id_mac) {

}
int Casino::Total_Memory(){

}
std::list<Machine *> *Casino::List_Types(const std::string& Type, std::ostream &f ){

}
std::list<std::string> *Casino::Ranking_of_the_weaks(){

}
std::list<Machine *> *Casino::Ranking_of_the_most_used(){

}
std::list<User *> *Casino::Most_Frequent_Users(){

}
std::list<User *> *Casino::Most_Wins_Users(){

}
void Casino::Report(const std::string& xml_file){

}
void Casino::Up_Neighbour_Probability(Machine *M_win, float R, std::list<Machine *> &list_machine_neighbour){

}

void Casino::Run(bool Debug) {

}
