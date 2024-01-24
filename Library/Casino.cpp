//
// Created on 06/11/23.
//

#include <utility>
#include "pugixml/pugixml.hpp"

#include "Headers/Casino.h"

Casino::Casino(std::string name): NAME{name}{}

Casino::~Casino(){

}

bool Casino::Load(const std::string &file) {
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(file.c_str());
    if (!result) {
        std::cout << "Error loading file: " << file << std::endl;
        return false;
    }

    pugi::xml_node data = doc.child("DATA");

    // Process SETTINGS
    pugi::xml_node settings = data.child("SETTINGS");
    std::string name = settings.child_value("NAME");
    std::string maxPlayersStr = settings.child_value("MAX_PLAYERS");
    std::string jackpotRadiusStr = settings.child_value("JackpotRadius");

    std::cout << "Casino Name: " << name << std::endl;
    std::cout << "Max Players: " << maxPlayersStr << std::endl;
    std::cout << "Jackpot Radius: " << jackpotRadiusStr << std::endl;

    // Convert strings to integers
    int maxPlayers = std::stoi(maxPlayersStr);
    int jackpotRadius = std::stoi(jackpotRadiusStr);
    // Set them to your class members
    // NAME = name;
    // MAX_Players = maxPlayers;
    // JackpotRadius = jackpotRadius;

    // Process MACHINELIST
    pugi::xml_node machineList = data.child("MACHINELIST");
    for (pugi::xml_node machine = machineList.child("MACHINE"); machine; machine = machine.next_sibling("MACHINE")) {
        std::string gameType = machine.child_value("GAME");
        int x = std::stoi(machine.child_value("X"));
        int y = std::stoi(machine.child_value("Y"));

        std::cout << "Machine Game:" << gameType << std::endl;
        std::cout << "Location X: " << x << std::endl;
        std::cout << "Location Y: " << y << std::endl;



        Machine* m = nullptr;
        if (gameType == " Blackjack ") {
            m = new Blackjack(x, y);
        } else if (gameType == " Roulette ") {
            m = new Roulette(x, y);
        } else if (gameType == " Classic Slots ") {
            m = new ClassicSlot(x, y);
        } else if (gameType == " Craps ") {
            m = new Craps(x, y);
        }

        if (m) {
            Add(m);
        }
        std::cout << std::endl;
    }

    return true;
}


[[maybe_unused]] bool Casino::Add(User *usr){
    if(usr== nullptr) cerr << "Null  pointer passed";
    l_users.push_back(usr);
}
bool Casino::Add(Machine *m){

    if ( m== nullptr ) return false;
    /** Get machine position **/
    pair<int, int> machine_pos;
    machine_pos = m->getPosition();
    /** Check if machine position is already taken **/
    bool result = checkMachinePositionAvailability(machine_pos);
    if (result){
        databaseAddMachine(m);
        return true;
    } else { cout << "Machine position already taken" ;}



}

bool Casino::checkMachinePositionAvailability(pair<int,int> position ){
    for(const auto &element : m_positions ){
        const std::pair<int,int> &el_position = element.first; /** gets the key **/
        if (position == el_position) { return false;}
    }
    return true;
}

void Casino::databaseAddMachine(Machine *m){
    MACHINE_TYPE type = m->getType();
    m_machines[type].push_back(m);
    switch (type) {
        case MACHINE_TYPE::BLACKJACK:
            l_Blackjack_Machines.push_back(m);
            break;
        case MACHINE_TYPE::ROULETTE:
            l_Roulette_Machines.push_back(m);
            break;
        case MACHINE_TYPE::CLASSIC_SLOT:
            l_classicSlots_Machines.push_back(m);
            break;
        case MACHINE_TYPE::CRAPS:
            l_Craps_Machines.push_back(m);
            break;
        default:
            cout << "Machine/Type not created yet...." ;
    }
    pair<int,int> pos;
    pos = m->getPosition();
    uint32_t id = m->getUID();
   // m_positions[pos] = id;
    auto it = m_positions.begin();
    m_positions.insert(it, std::make_pair(pos,id));
    m_machine_id[id] = m;

}


void Casino::Listing(std::ostream &f){

}

void Casino::Listing(float X, std::ostream &f){

}

void Casino::TurnOff(const int id_mac){
    auto it = m_machine_id.find('id_mac');
    if (it != m_machine_id.end())
        it->second->setState(MACHINE_STATE::OFF);
    else cout << "Machine ID not found!";
}

// m_machine_id.erase (it);

MACHINE_STATE Casino::getState(const int id_mac) {
    auto it = m_machine_id.find('id_mac');
    if (it != m_machine_id.end())
       return it->second->getState();
    else cout << "Machine ID not found!";
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

void Casino::ReadPeopleFile(int n) {
    string line;
    ifstream myfile("../Files/I/pessoas.txt");

    if (myfile.is_open()) {
        int usersAdded = 0;

        while (getline(myfile, line) && usersAdded < n) {
            stringstream aux(line);

            string id, name, city, age;
            getline(aux, id, '\t');
            getline(aux, name, '\t');
            getline(aux, city, '\t');
            getline(aux, age, '\t');

            User* user = new User(id.data(), name, city, stoi(age));

            // Check if the user with this ID already exists in the list
            bool userExists = false;
            for (const auto& existingUser : l_users) {
                if (existingUser->getId() == user->getId()) {
                    userExists = true;
                    break;
                }
            }

            if (userExists) {
                cout << "User with ID " << user->getId() << " already exists. Try again." << endl;
                delete user;  // Free the memory allocated for the user
            } else {
                Add(user);
                usersAdded++;
            }
        }

        myfile.close();
        cout << " Success loading users" ;
    } else{
        cout << " Error opening users File";
    }
}



void Casino::Run(bool Debug) {

}


