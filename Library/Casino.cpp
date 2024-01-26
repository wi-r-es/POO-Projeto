//
// Created on 06/11/23.
//


#include "Headers/Casino.h"



#include "pugixml/pugixml.hpp"

#ifdef _WIN32
string clients_file { "..\\Files\\I\\pessoas.txt" };
string logfile { "..\\Files\\O\\applog.csv" };
string error_logfile { "..\\Files\\O\\applog.csv" };
#else
 string clients_file { "../Files/I/pessoas.txt" } ;
 string logfile { "../Files/O/applog.csv" } ;
 string error_logfile { "../Files/O/error_log.csv" } ;

#endif

Casino::Casino(std::string name): NAME{std::move(name)}, MAX_Players{},JackpotRadius{}{
    rolex = new Clock();
}
Casino::Casino(std::string name,int max, int jradius): NAME{std::move(name)}, MAX_Players{max},JackpotRadius{jradius}{
    rolex = new Clock();
}

Casino::~Casino(){
    /** Delete all machines from the m_machine_id map **/
    for(auto & it : m_machine_id) {
        delete it.second;
    }
    /** Clear other containers without deleting the elements
     *         as they are already deleted from m_machine_id **/
    m_machine_id.clear();
    m_positions.clear();
    m_machines.clear(); //maybe, still TBD
    v_classicSlots_Machines.clear();
    v_Blackjack_Machines.clear();
    v_Roulette_Machines.clear();
    v_Craps_Machines.clear();
    v_Broken_Machines.clear();
    /** Delete users and related container **/
    for(auto & l_user : l_users) {
        delete l_user;
    }
    l_users.clear();
    /** Delete other class owned resources **/
    delete rolex;
}

bool Casino::Load(const std::string &file) {
    logging(logfile, __FUNCTION__ , "Loading casino from file");
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
            logging(error_logfile, __FUNCTION__, "Error adding machine to casino. Position already taken.");
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
        logging(logfile, __FUNCTION__ , message);
        beautify(message, '*');
    } else{
        logging(error_logfile, __FUNCTION__ , "Error loading users file");
        cerr << " Error opening users File";
    }
}

// Casino current state! DONE
void Casino::Listing(std::ostream &f){
    beautify("Machines in casino without any ordering");
    for (const auto &it : m_machine_id) {
        f << it.second->toString() << '\n';
    }
    f << "[[Users]]\n";
    for (const auto &user : l_users) {
        f << user->toString() << '\n';
    }
    f << "[[Containers size]]\n";
    f << VectorsSize() << '\n';

}

void Casino::Listing(float X, std::ostream &f){

    for(auto & it : m_machine_id) {
        if (it.second->getWinProbability() > X) {
           f<< it.second->toStringOut()<<'\n';
        }
    }
}

void Casino::TurnOff(const int id_mac){
    auto it = m_machine_id.find(id_mac);
    if (it != m_machine_id.end())
        it->second->setState(MACHINE_STATE::OFF);
    else cout << "Machine ID not found!";
}
void Casino::BrokenMachine(const int id_mac){
    auto it = m_machine_id.find(id_mac);
    if (it != m_machine_id.end()) {
        it->second->setState(MACHINE_STATE::BROKEN);
        v_Broken_Machines.push_back(it->second);
    }
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
        logging(error_logfile, __FUNCTION__, ex.what());
        return MACHINE_STATE::NONEXISTENT;
    }
}

Clock *Casino::getClock() const {
    return rolex;
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


std::list<Machine *> *Casino::List_Types(const MACHINE_TYPE Type, std::ostream &f ){
    try{
        switch (Type) {
            case MACHINE_TYPE::BLACKJACK:
                if (v_Blackjack_Machines.empty()) { throw runtime_error{"Empty Blackjack List"}; }
                machine = getRandomMachineFromVector(type, v_Blackjack_Machines);
                break;
            case MACHINE_TYPE::ROULETTE:
                if (v_Roulette_Machines.empty()) { throw runtime_error{"Empty Roulette List"}; }
                machine = getRandomMachineFromVector(type, v_Roulette_Machines);
                break;
            case MACHINE_TYPE::CLASSIC_SLOT:
                if (v_classicSlots_Machines.empty()) { throw runtime_error{"Empty ClassicSlot List"}; }
                machine = getRandomMachineFromVector(type, v_classicSlots_Machines);
                break;
            case MACHINE_TYPE::CRAPS:
                if (v_Craps_Machines.empty()) { throw runtime_error{"Empty Craps List"}; }
                machine = getRandomMachineFromVector(type, v_Craps_Machines);
                break;
            default:
                cerr << "Type not used, some error has occurred....";
                throw runtime_error{"Type not used, some error has occurred...."};
        }
    }catch(runtime_error &ex){
        cerr << ex.what();
        logging(error_logfile, __FUNCTION__ , ex.what());
        return nullptr;
    }
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
    Machine* mac{};
    int attempts = 0;
    auto num_macs = m_machine_id.size();

    do {
        auto type = getRandomType();
        mac = getRandomMachineByType(type);
        auto state = mac->getState();
        if (state != MACHINE_STATE::BROKEN) {
            break; /** Found a working machine **/
        }
        ++attempts;
    } while(attempts <= num_macs);

    if (mac->getState() == MACHINE_STATE::BROKEN || mac->getState() == MACHINE_STATE::OFF || mac == nullptr) {
        cout << "No working machines available.\n";
        return; /** Early exit if no working machine is found **/
    }

    try{
        float temp = mac->getTemperature();
        if(temp > 90.0f)
        {
            cout << "TEMP: " << temp << endl;
            throw runtime_error{"Machine malfunction due to high temperature."};
        }
        mac->Play(usr);
        if(mac->getFailureProbability() == 0.8f) {
            throw runtime_error{"Machine malfunction due to failure in the system hardware."};
        }

    } catch (runtime_error &ex) {
        cerr<<"An error as occurred while trying to use machine\n\t"
            << '[' << mac->getUID() << ']' << " ... -> " << ex.what();
        logging(error_logfile, "[[EXCEPTION CAUGHT]--[WHILE_TRYING_TO_USE_MACHINE]]", ex.what());
        auto [x,y] = mac->getPosition();
        string s = "[[ {" + to_string(mac->getUID()) +  "},{" +
                machineTypeToString(mac->getType()) + "} at { [" + to_string(x) + "," + to_string(y) + "] }" +
                " with {" + to_string(mac->getTemperature()) + "º Temperature} " + "]]";
        logging(error_logfile, "[[SHUTTING DOWN MACHINE]]", s);
        BrokenMachine(mac->getUID());
    }

    logging(logfile, __FUNCTION__, mac->toString());
    //Wait(1000);
    //auto current_time =  rolex->getTime();
    //printTime(current_time);
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
    /*
    auto it = m_machines.find(type);
    if (it == m_machines.end() || it->second.empty()) {
        return nullptr; // No machines of this type
    }
     */
    Machine* machine= nullptr;
    try{
        switch (type) {
            case MACHINE_TYPE::BLACKJACK:
                if (v_Blackjack_Machines.empty()) { throw runtime_error{"Empty Blackjack List"}; }
                machine = getRandomMachineFromVector(type, v_Blackjack_Machines);
                break;
            case MACHINE_TYPE::ROULETTE:
                if (v_Roulette_Machines.empty()) { throw runtime_error{"Empty Roulette List"}; }
                machine = getRandomMachineFromVector(type, v_Roulette_Machines);
                break;
            case MACHINE_TYPE::CLASSIC_SLOT:
                if (v_classicSlots_Machines.empty()) { throw runtime_error{"Empty ClassicSlot List"}; }
                machine = getRandomMachineFromVector(type, v_classicSlots_Machines);
                break;
            case MACHINE_TYPE::CRAPS:
                if (v_Craps_Machines.empty()) { throw runtime_error{"Empty Craps List"}; }
                machine = getRandomMachineFromVector(type, v_Craps_Machines);
                break;
            default:
                cerr << "Type not used, some error has occurred....";
        }
    }catch(runtime_error &ex){
        cerr << ex.what();
        logging(error_logfile, __FUNCTION__ , ex.what());
        return machine;
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

void Casino::changeMachineFailProbability() {
    auto type = getRandomType();
    auto mac = getRandomMachineByType(type);
    mac->setFailureProbability(0.8); // Set probability to 80%
}

void Casino::RandomOddImprovement(){
    auto type = getRandomType();
    auto mac = getRandomMachineByType(type);
    mac->setWinProbability(mac->getWinProbability()+0.15f); // Set probability to 80%
}

void Casino::check_routine() {
    auto TimeGoneBy = [](std::chrono::steady_clock::time_point tp1,
                            std::chrono::steady_clock::time_point tp2){
        auto temp = chrono::duration_cast<chrono::seconds>(tp2 - tp1);
        return (temp.count());
    };

    auto it = v_Broken_Machines.begin();
    while (it != v_Broken_Machines.end()) {
        Machine* mac = *it;
        MACHINE_STATE state = mac->getState();
        auto type = mac->getType();
        auto time = std::chrono::steady_clock::now();

        //Wait(5);
        //cout << mac->toStringOut();
        //Wait(15);
        auto timeInMaintenance = TimeGoneBy(mac->getTimeInMaintenance(),time);
        if (state == MACHINE_STATE::BROKEN) {
            // Move machine to maintenance
            mac->setState(MACHINE_STATE::MAINTENANCE);
            mac->setMaintenanceTime(time);
            mac->incrementFailures();
            removeFromTypeVector(mac, type);
            ++it;
        } else if (state == MACHINE_STATE::MAINTENANCE && ( timeInMaintenance >= 5 ) ) {
            /** Reactivate machine **/
            //Wait(5);
            auto s = mac->toStringOut();
            s.append(" -- was in maitenance for ") + to_string(timeInMaintenance);
            logging(logfile, s, to_string(timeInMaintenance));

            mac->setState(MACHINE_STATE::ON);
            mac->reset();
            addToTypeVector(mac,type);
            it = v_Broken_Machines.erase(it);  /** Remove fixed machine and update iterator **/
            cout << "Machine removed from broken vector";
        } else {
            ++it;
        }
    }
}
void Casino::removeFromTypeVector(Machine* machine, MACHINE_TYPE type) {
    vector<Machine*> *machine_vector;

    switch (type) {
        case MACHINE_TYPE::BLACKJACK:
            machine_vector = &v_Blackjack_Machines;
            break;
        case MACHINE_TYPE::ROULETTE:
            machine_vector = &v_Roulette_Machines;
            break;
        case MACHINE_TYPE::CLASSIC_SLOT:
            machine_vector = &v_classicSlots_Machines;
            break;
        case MACHINE_TYPE::CRAPS:
            machine_vector = &v_Craps_Machines;
            break;
        default:
            std::cerr << "Unknown machine type encountered.";
            return;
    }

    try{
        if(machine_vector->empty()) throw runtime_error{"Vector is empty"};
        auto it = find(machine_vector->begin(), machine_vector->end(), machine);
        if (it != machine_vector->end()) {
            machine_vector->erase(it);
        }
    } catch( runtime_error &ex){
        logging(error_logfile, __FUNCTION__ , ex.what());
        cerr << ex.what();
    }
}
void Casino::addToTypeVector(Machine* machine, MACHINE_TYPE type) {
    vector<Machine*> *machine_vector;

    switch (type) {
        case MACHINE_TYPE::BLACKJACK:
            machine_vector = &v_Blackjack_Machines;
            break;
        case MACHINE_TYPE::ROULETTE:
            machine_vector = &v_Roulette_Machines;
            break;
        case MACHINE_TYPE::CLASSIC_SLOT:
            machine_vector = &v_classicSlots_Machines;
            break;
        case MACHINE_TYPE::CRAPS:
            machine_vector = &v_Craps_Machines;
            break;
        default:
            std::cerr << "Unknown machine type encountered.";
            return;
    }
    machine_vector->push_back(machine);
    cout << "Machine re-added to vector";
}

void Casino::printVectorsSize(){
    auto s1 = v_Blackjack_Machines.size();
    auto s2 = v_Craps_Machines.size();
    auto s3 = v_classicSlots_Machines.size();
    auto s4 = v_Roulette_Machines.size();
    auto b = v_Broken_Machines.size();

    cout << "Items in vectors: \n" << "\tBlackjack: " << s1
            << "\n\tCraps: " << s2 << "\n\tClassicSlots: " << s3
            << "\n\tRoulette: " << s4 << "\n\tBrokenMachines: " << b << endl;
}
string Casino::VectorsSize(){
    auto s1 = v_Blackjack_Machines.size();
    auto s2 = v_Craps_Machines.size();
    auto s3 = v_classicSlots_Machines.size();
    auto s4 = v_Roulette_Machines.size();
    auto b = v_Broken_Machines.size();

    string final =  "Items in vectors: \n" ;
    final.append("\tBlackjack: ");
    final.append(to_string(s1));
    final.append("\n\tCraps: ");
    final.append(to_string(s2));
    final.append("\n\tClassicSlots: ");
    final.append(to_string(s3));
    final.append("\n\tRoulette: ");
    final.append(to_string(s4));
    final.append("\n\tBrokenMachines: ");
    final.append(to_string(b));
    //final.append();
    return final;
}