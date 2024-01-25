//
// Created on 06/11/23.
//


#include "Headers/Casino.h"



#include "pugixml/pugixml.hpp"

#ifdef _WIN32
string clients_file { "..\\Files\\I\\pessoas.txt" };
string logfile { "..\\Files\\O\\applog.csv" };
#else
string clients_file { "../Files/I/pessoas.txt" } ;
string logfile { "../Files/O/applog.csv" } ;

#endif

Casino::Casino(std::string name): NAME{std::move(name)}, MAX_Players{},JackpotRadius{}{
    clock = new Clock();
}
Casino::Casino(std::string name,int max, int jradius): NAME{std::move(name)}, MAX_Players{max},JackpotRadius{jradius}{
    clock = new Clock();
}

Casino::~Casino(){

    for(auto it = m_machines.begin(); it != m_machines.end(); ++it) {
        for (auto &machine : it->second) {
            delete machine;
        }
    }

    for(auto it = l_users.begin(); it != l_users.end(); ++it) {
        delete *it;
    }

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
        usr->setMoney(5000);
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
    /** Check if a machine with the same ID already exists **/
    if (m_machine_id.find(id) != m_machine_id.end()) {
        cerr << "Machine with ID " << id << " already exists." << endl;
        return;
    }
    /** Add the machine to the appropriate vector and maps **/
    m_machines[type].push_back(m);
    m_positions[pos] = id;
    m_machine_id[id] = m;

    switch (type) {
        case MACHINE_TYPE::BLACKJACK:
            v_Blackjack_Machines.push_back(m);
            break;
        case MACHINE_TYPE::ROULETTE:
            v_Roulette_Machines.push_back(m);
            break;
        case MACHINE_TYPE::CLASSIC_SLOT:
            v_classicSlots_Machines.push_back(m);
            break;
        case MACHINE_TYPE::CRAPS:
            v_Craps_Machines.push_back(m);
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
        auto message = " Success Loading " + to_string(count) + " users ";
        beautify(message, '*');
    } else{
        cerr << " Error opening users File";
    }
}

// Estado atual do casino
void Casino::Listing(std::ostream &f){
    beautify(" Machines in casino without any ordering ");
    Wait(10);
    //cout << "******************************************" << endl;
    //cout << "* Machines in casino without any ordering *" << endl;
    //cout << "Machines in casino without any ordering:" << endl;

    for(auto & it : m_machine_id) {
        string s = it.second->toStringOut();
        f << s << endl;
        Wait(5);
    }
}

void Casino::Listing(float X, std::ostream &f){

    for(auto & it : m_machine_id) {
        if (it.second->getWinProbability() > X) {
            string s = it.second->toStringOut();
            f << s << endl;
        }
    }
}

void Casino::TurnOff(const int id_mac){
    auto it = m_machine_id.find(id_mac);
    if (it != m_machine_id.end())
        it->second->setState(MACHINE_STATE::OFF);
    else cout << "Machine ID not found!";
}

// m_machine_id.erase (it);

MACHINE_STATE Casino::getState(const int id_mac) {
    try {
        auto it = m_machine_id.find(id_mac);
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

Clock *Casino::getClock() const {
    return clock;
}

size_t Casino::Total_Memory() const{
    size_t totalSize = sizeof(*this); /** Size of the Casino object itself **/
    /** Calculate the size of all unique machines in m_machine_id map **/
    for (const auto& pair : m_machine_id) {
        totalSize += sizeof(pair.first) + sizeof(Machine*); /** Size of the map entry (ID and pointer) **/
        totalSize += sizeof(*(pair.second)); /** Size of the Machine object pointed to by the pointer **/
    }
    /** Add the size of collections storing pointers to machines **/
    totalSize += m_positions.size() * sizeof(std::pair<const std::pair<int, int>, uint16_t>); /** Size of m_positions map **/
    totalSize += m_machines.size() * sizeof(std::pair<const MACHINE_TYPE, std::list<Machine *>>); /** Size of m_machines map **/

    // if map is indeed never used or initialized this shall be deleted
    for (const auto& pair : m_machines) {
        totalSize += pair.second.size() * sizeof(Machine*); /** Size of the list of pointers in each map entry **/
    }

    /** Add the size of specific machine lists **/
    totalSize += v_classicSlots_Machines.size();         /** Size of l_classicSlots_Machines list **/
    totalSize += v_Blackjack_Machines.size();            /** Size of l_Blackjack_Machines list **/
    totalSize += v_Roulette_Machines.size();             /** Size of l_Roulette_Machines list **/
    totalSize += v_Craps_Machines.size();                /** Size of l_Craps_Machines list **/
    /** Add the size of the user list **/
    totalSize += l_users.size() * sizeof(User*);         /** Size of l_users list **/
    return totalSize;
}
std::list<Machine *> *Casino::List_Types(const std::string& Type, std::ostream &f ){

}
std::list<std::string> *Casino::Ranking_of_the_weaks(){
    vector<Machine*> v_broken = v_Broken_Machines;

    sort(v_broken.begin(), v_broken.end(), [](Machine* m1, Machine* m2) {
        return m1->getFailures() > m2->getFailures();
    });

    list<string> *l_ranking;
    for (auto it = v_broken.begin(); it != v_broken.end(); it++) {
        l_ranking->push_back("MACHINE ID: " + to_string((*it)->getUID()) + " FAILURES: " + to_string((*it)->getFailures()) + "\n");
    }
    return l_ranking;
}


std::list<Machine *> *Casino::Ranking_of_the_most_used(){

    map<MACHINE_TYPE, std::list<Machine *>> m_machine = m_machines;

    for(auto &pair : m_machine){
        pair.second.sort([](Machine* m1, Machine* m2) {
            return m1->getUsage() > m2->getUsage();
        });
    }

    list<string> *l_ranking;
    for (auto it = m_machine.begin(); it != m_machine.end(); ++it) {
        if (!it->second.empty()) { // Check if the list is not empty
            Machine* machine = it->second.front(); // Get the first Machine* in the list
            l_ranking->push_back("MACHINE ID: " + std::to_string(machine->getID()) + " USAGE: " + std::to_string(machine->getUsage()) + "\n");
        }
    }
}


std::list<User *> *Casino::Most_Frequent_Users(){
    list<User*> *l_frequent_users;
    l_frequent_users->sort([] (User* u1, User* u2) {
        return u1->getTimeSpent() > u2->getTimeSpent();
    });

    return  l_frequent_users;
}


std::list<User *> *Casino::Most_Wins_Users(){

    list<User*> *l_wins_users;
    l_wins_users->sort([] (User* u1, User* u2) {
        return u1->getPrizesWon() > u2->getPrizesWon();
    });

    return l_wins_users;

}


void Casino::Report(const std::string& xml_file){

}

float Casino::DistanceBetweenPoints(int first, int second, int first1, int second1) {
    return sqrt(pow(first1 - first, 2) + pow(second1 - second, 2));
}

void Casino::Up_Neighbour_Probability(Machine *M_win, float R, std::list<Machine *> &list_machine_neighbour){

    for(Machine* m : list_machine_neighbour){
        if(m != M_win){
            float distance = DistanceBetweenPoints(M_win->getPosition().first, M_win->getPosition().second, m->getPosition().first, m->getPosition().second);
            if(distance <= R){
                m->setWinProbability(m->getWinProbability() + 0.1);
            }
        }
    }
}





void Casino::Run() {
    auto usr = getRandomUser();
    auto type = getRandomType();
    auto mac = getRandomMachineByType(type);

    mac->Play(usr);
    logging(logfile, __FUNCTION__, mac->toString());

    cout << "Current time " << clock->getTime() << endl;

}

User* Casino::getRandomUser(){
    if (l_users.empty()) {
        return nullptr; /** check if list is empty **/
    }
    /** Get the size of the list **/
    size_t size = l_users.size();
    /** Generate a random position **/
    int randomPos = randomNumberGeneratorInterval(0, static_cast<int>(size) - 1);
    /** Advance the iterator to the random position **/
    auto it = l_users.begin();
    std::advance(it, randomPos);
    return *it; /** Return the random user **/
}


Machine* getRandomMachineFromVector(MACHINE_TYPE type, const std::vector<Machine *>& vec) {
    auto machineCount = vec.size();
    int randomIndex = randomNumberGeneratorInterval(0, static_cast<int>(machineCount) - 1);
    auto t = vec.at(randomIndex);
    return t;
}

Machine* Casino::getRandomMachineByType(MACHINE_TYPE type){
    /** Check if there are machines of the given type **/
    auto it = m_machines.find(type);
    if (it == m_machines.end() || it->second.empty()) {
        return nullptr; // No machines of this type
    }
    Machine* machine= nullptr;
    switch (type) {
        case MACHINE_TYPE::BLACKJACK:
            machine = getRandomMachineFromVector(type, v_Blackjack_Machines);
            break;
        case MACHINE_TYPE::ROULETTE:
            machine = getRandomMachineFromVector(type,v_Roulette_Machines);
            break;
        case MACHINE_TYPE::CLASSIC_SLOT:
            machine = getRandomMachineFromVector(type,v_classicSlots_Machines);
            break;
        case MACHINE_TYPE::CRAPS:
            machine = getRandomMachineFromVector(type,v_Craps_Machines);
            break;
        default:
            cerr << "Type not used, some error has occured....";
    }
    return machine;
}
MACHINE_TYPE Casino::getRandomType(){
    /** Only randomizes the machines types at use **/
    static const MACHINE_TYPE typesInUse[] = {
            MACHINE_TYPE::CLASSIC_SLOT,
            MACHINE_TYPE::BLACKJACK,
            MACHINE_TYPE::ROULETTE,
            MACHINE_TYPE::CRAPS
    };
    int randomIndex = randomNumberGeneratorInterval(0, sizeof(typesInUse) / sizeof(typesInUse[0]) - 1);
    return typesInUse[randomIndex];
}


