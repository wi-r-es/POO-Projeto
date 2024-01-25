//
// Created on 06/11/23.
//
#include <utility>

#include "Headers/Casino.h"
#include "pugixml/pugixml.hpp"

#ifdef _WIN32
string clients_file { "..\\Files\\I\\pessoas.txt" };
string logfile { "..\\Files\\O\\applog.csv" };
#else
string clients_file { "../Files/I/pessoas.txt" } ;
string logfile { "../Files/O/applog.csv" } ;

#endif

Casino::Casino(std::string name): NAME{std::move(name)}, MAX_Players{},JackpotRadius{}{}
Casino::Casino(std::string name,int max, int jradius): NAME{std::move(name)}, MAX_Players{max},JackpotRadius{jradius}{}

Casino::~Casino(){

}

bool Casino::Load(const std::string &file) {
    pugi::xml_document doc;
    if (!doc.load_file(file.c_str())) {
        std::cout << "Error loading file: " << file << std::endl;
        return false;
    }
    auto data = doc.child("DATA");

    auto settings = data.child("SETTINGS");
    NAME = settings.child_value("NAME");
    MAX_Players = std::stoi(settings.child_value("MAX_PLAYERS"));
    JackpotRadius = std::stoi(settings.child_value("JackpotRadius"));
    std::cout << "Casino Name: " << NAME << std::endl;
    std::cout << "Max Players: " << MAX_Players << std::endl;
    std::cout << "Jackpot Radius: " << JackpotRadius << std::endl;

    auto machineList = data.child("MACHINELIST");
    for (auto machine = machineList.child("MACHINE"); machine; machine = machine.next_sibling("MACHINE")) {
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

        if (m && !Add(m)) {
            logging(logfile, __FUNCTION__, "Error adding machine to casino.");
            delete m; //clean up
        }
        std::cout << std::endl;
    }
    return true;
}


bool Casino::Add(User *usr){
    try {
        l_users.push_back(usr);
        return true;
    } catch (runtime_error& ex){
        cerr<<"An error as occured... -> " << ex.what();
        return false;
    }
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
    } else {
        cerr << "Machine position already taken\n" ;
        cout << endl << endl<<endl<<endl;
        return false;}
}

bool Casino::checkMachinePositionAvailability(pair<int,int> position ){
    for(const auto &element : m_positions ){
        const auto &el_position = element.first; /** gets the key **/
        if (position == el_position) { return false;}
    }
    return true;
}

void Casino::databaseAddMachine(Machine *m){
    MACHINE_TYPE type = m->getType();
    auto pos = m->getPosition();
    uint32_t id = m->getUID();

    // Check if a machine with the same ID already exists
    if (m_machine_id.find(id) != m_machine_id.end()) {
        cerr << "Machine with ID " << id << " already exists." << endl;
        return;
    }

    /** Add the machine to the appropriate list and maps **/
    m_machines[type].push_back(m);
    m_positions[pos] = id;
    m_machine_id[id] = m;

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
            cout << "Machine/Type not created yet....\n";
    }
}


void Casino::ReadPeopleFile() {
    string line;
    ifstream myfile{clients_file, ios::in};

    if (myfile.is_open()) {
        int count{};
        while (getline(myfile, line) ) {
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
                delete user;
            } else {
                if(Add(user)) {
                    //cout << "User added to casino.\n";
                    count++;
                }
            }
        }
        myfile.close();
        cout << " Success loading " << count << "users.\n" ;
    } else{
        cout << " Error opening users File";
    }
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
    try {
        auto it = m_machine_id.find('id_mac');
        if (it != m_machine_id.end())
            return it->second->getState();
        else throw runtime_error{"Machine not found"};
    }
    catch(const runtime_error& ex){
        //string log = ex.what()
        logging(logfile, __FUNCTION__, ex.what());
        return MACHINE_STATE::NONEXISTENT;
    }
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


