//
// Created on 06/11/23.
//


#include "Headers/Casino.h"



#include "pugixml/pugixml.hpp"

#ifdef _WIN32
string clients_file { "..\\Files\\I\\pessoas.txt" };
string logfile { "..\\Files\\O\\applog.csv" };
string error_logfile { "..\\Files\\O\\applog.csv" };
string casinoFile { "..\\Files\\O\\casinoState.txt" } ;
string reportfile { "..\\Files\\O\\casino_report.xml" } ;
#else
string clients_file { "../Files/I/pessoas.txt" } ;
string logfile { "../Files/O/applog.csv" } ;
string error_logfile { "../Files/O/error_log.csv" } ;
string casinoFile { "../Files/O/casinoState.txt" } ;
string reportfile { "../Files/O/casino_report.xml" } ;
#endif


namespace usefulFT{
    /** specific content for C++ 17, for C++ 20 concepts can be used **/

    /*******************************************************************************************************************************************************************
     * @brief Template structure to check for the existence of a `toString` method in a class.
     *
     * This template structure `has_toString_method` is a type trait used to determine if a given class `T` has a `toString` member function. It makes use of SFINAE
     * (Substitution Failure Is Not An Error) to check for the existence of `toString`. It inherits from `std::true_type` or `std::false_type` based on the check.
     *
     * @tparam T The type to check for the `toString` method.
     * @tparam The second template parameter is used for SFINAE and is defaulted to `std::void_t<>`.
     *
     * @note This structure is useful in compile-time checks and static assertions to ensure that a class provides a specific interface.
     *******************************************************************************************************************************************************************/
    template<typename T, typename = std::void_t<>>
    struct has_toString_method : std::false_type {
    };
    template<typename T>
    struct has_toString_method<T, std::void_t<decltype(std::declval<T>().toString())>> : std::true_type {
    };

    /*******************************************************************************************************************************************************************
     * @brief Prints elements of a container assuming each element has a `toString` method.
     *
     * This function template iterates over a container and prints each element using its `toString` method. It statically asserts that the container's value type is
     * `Machine` and that `Machine` has a `toString` method.
     *
     * @tparam Container The type of the container (should contain `Machine` objects).
     * @param container A constant reference to the container whose elements are to be printed.
     *
     * @note This function is useful for printing details of objects stored in a collection in a standardized format.
     *******************************************************************************************************************************************************************/
    template<typename Container>
    void printElements(const Container &container) {
        /** Check if the container's value_type is Machine **/
        static_assert(std::is_same_v<typename Container::value_type, Machine>,
                      "Container does not contain Machine objects");

        /** Check if Machine has a toString method **/
        static_assert(has_toString_method<Machine>::value, "Machine does not have a toString method");

        for (const auto &element: container) {
            std::cout << element.toString() << std::endl;
        }
    }

    /*******************************************************************************************************************************************************************
     * @brief Sorts elements of a container in a stable manner based on a comparison function.
     *
     * This function template sorts the elements of a container using `std::stable_sort` for random-access containers or `sort` for `std::list`. It requires a
     * comparison function `comp` that compares the dereferenced elements (pointers) of the container.
     *
     * @tparam Container The type of the container to be sorted (e.g., vector, list of pointers).
     * @tparam Compare The type of the comparison function.
     * @param container A reference to the container to be sorted.
     * @param comp The comparison function used for sorting.
     *
     * @note Specialized for handling `std::list` differently as it does not support random-access iterators required by `std::stable_sort`.
     *******************************************************************************************************************************************************************/
    template <typename Container, typename Compare>
    void stableSortContainer(Container& container, Compare comp) {
        std::stable_sort(container.begin(), container.end(),
                         [&](const auto& a, const auto& b) { return comp(*a, *b); });
    }

    template <typename T, typename Compare>
    void stableSortContainer(std::list<T*>& container, Compare comp) {
        container.sort([&](const auto& a, const auto& b) { return comp(*a, *b); });
    }

    /*******************************************************************************************************************************************************************
     * @brief Sorts elements representing users in a container in a stable manner based on a comparison function.
     *
     * Similar to `stableSortContainer`, this function template sorts user-related elements in a container. It is specifically named to reflect its typical use case
     * with user data. It uses `std::stable_sort` or `sort` depending on the container type and requires a comparison function.
     *
     * @tparam Container The type of the container holding user data.
     * @tparam Compare The type of the comparison function.
     * @param container A reference to the container to be sorted.
     * @param comp The comparison function used for sorting.
     *
     * @note Specialized for sorting user data, useful in contexts like user management systems or leaderboards.
     *******************************************************************************************************************************************************************/
    template <typename Container, typename Compare>
    void stableSortUsers(Container& container, Compare comp) {
        std::stable_sort(container.begin(), container.end(),
                         [&](const auto& a, const auto& b) { return comp(*a, *b); });
    }
    template <typename T, typename Compare>
    void stableSortUsers(std::list<T*>& container, Compare comp) {
        container.sort([&](const auto& a, const auto& b) { return comp(*a, *b); });
    }
}

Casino::Casino(std::string name): NAME{std::move(name)},JackpotRadius{}{
    rolex = new Clock();
}
Casino::Casino(std::string name,int max, int jradius): NAME{std::move(name)},JackpotRadius{jradius}{
    rolex = new Clock();
}

Casino::~Casino(){
    /** Delete users and related container **/
    for(auto & l_user : l_users) {
        delete l_user;
    }
    l_users.clear();
    /** Delete all machines from the list and related container **/
    for(auto & l_machine : l_machines) {
        delete l_machine;
    }
    l_machines.clear();
    /** Clear other containers without deleting the elements
     *         as they are already deleted from m_machine_id **/
    m_machine_id.clear();
    m_positions.clear();
    v_classicSlots_Machines.clear();
    v_Blackjack_Machines.clear();
    v_Roulette_Machines.clear();
    v_Craps_Machines.clear();
    v_Broken_Machines.clear();

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
    std::cout << "Casino Name: " << NAME << std::endl;
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
    l_machines.push_back(m);
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
    beautify(" Machines in casino without any ordering ");
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
    beautify(" Machines in casino with winning odd higher than X");
    for(auto & it : m_machine_id) {
        if (it.second->getWinProbability() > X) {
           f<< it.second->toStringOut()<<'\n';
        }
    }
}

void Casino::ListMachinesUID(std::ostream &f){
    beautify(" Machines in casino by UID ");
    for(auto & it : m_machine_id) {
        f<< to_string(it.first) <<'\n';
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
    totalSize += l_machines.size() * sizeof(Machine*);
    for (const auto machine : l_machines) {
        totalSize += sizeof(*machine); // Size of each machine object
    }
    /** Add the size of collections storing pointers to machines **/
    totalSize += m_positions.size() * sizeof(std::pair<const std::pair<int, int>, uint16_t>); /** Size of m_positions map **/
    totalSize += m_machine_id.size() * sizeof(std::pair<uint16_t , Machine*>); /** Size of m_machine_id map **/


    /** Add the size of specific machine lists **/
    totalSize += v_classicSlots_Machines.size();         /** Size of l_classicSlots_Machines list **/
    totalSize += v_Blackjack_Machines.size();            /** Size of l_Blackjack_Machines list **/
    totalSize += v_Roulette_Machines.size();             /** Size of l_Roulette_Machines list **/
    totalSize += v_Craps_Machines.size();                /** Size of l_Craps_Machines list **/
    totalSize += v_Broken_Machines.size() * sizeof(Machine*);
    /** Add the size of the user list **/
    totalSize += l_users.size() * sizeof(User*);         /** Size of l_users list **/
    for (const auto user : l_users) {
        totalSize += sizeof(*user); // Size of each User object
    }
    if (rolex != nullptr) {
        totalSize += sizeof(*rolex);
    }
    return totalSize;
}


std::list<Machine *> *Casino::List_Types(const MACHINE_TYPE Type, std::ostream &f ){
    std::vector<Machine *> *vecvec= nullptr;
    auto list_by_type = new std::list<Machine *>;
    try{

        switch (Type) {
            case MACHINE_TYPE::BLACKJACK:
                if (v_Blackjack_Machines.empty()) { throw runtime_error{"Empty Blackjack List"}; }
                vecvec = &v_Blackjack_Machines;
                break;
            case MACHINE_TYPE::ROULETTE:
                if (v_Roulette_Machines.empty()) { throw runtime_error{"Empty Roulette List"}; }
                vecvec = &v_Roulette_Machines;
                break;
            case MACHINE_TYPE::CLASSIC_SLOT:
                if (v_classicSlots_Machines.empty()) { throw runtime_error{"Empty ClassicSlot List"}; }
                vecvec = &v_classicSlots_Machines;
                break;
            case MACHINE_TYPE::CRAPS:
                if (v_Craps_Machines.empty()) { throw runtime_error{"Empty Craps List"}; }
                vecvec = &v_Craps_Machines;
                break;
            default:
                cerr << "Type not used, some error has occurred....";

                throw runtime_error{"Type not used, some error has occurred...."};
        }
        List_Specific_Containers(*vecvec, *list_by_type);
    }catch(runtime_error &ex){
        f << ex.what();
        delete list_by_type; /** Clean up to avoid memory leak **/
        logging(error_logfile, __FUNCTION__ , ex.what());
        return nullptr;
    }

    return list_by_type;
}
std::list<std::string> *Casino::Ranking_of_the_weaks(){
    auto tempL = l_machines;
    auto l_ranking = new std::list<std::string> ;

    try{
        usefulFT::stableSortContainer(tempL, [](const Machine& a, const Machine& b) {
            return a.getFailures() > b.getFailures();
        });
        for(auto &m : tempL){
            l_ranking->push_back(m->toStringOut());
        }
    }catch(runtime_error &ex) {
        cout << ex.what();
        logging(error_logfile, __FUNCTION__, ex.what());
        return nullptr;
    }
    return l_ranking;
}


std::list<Machine *> *Casino::Ranking_of_the_most_used(){
    auto tempL = l_machines;
    auto l_ranking = new std::list<Machine *>;
    try{
        usefulFT::stableSortContainer(tempL, [](const Machine& a, const Machine& b) {
            return a.getUsage() > b.getUsage();
        });
        for(auto &m : tempL){
            l_ranking->push_back(m);
        }

    }catch(runtime_error &ex) {
        cout << ex.what();
        delete l_ranking; /** Clean up to avoid memory leak **/
        logging(error_logfile, __FUNCTION__, ex.what());
        return nullptr;
    }
    return l_ranking;
}


std::list<User *> *Casino::Most_Frequent_Users(){
    auto tempL = l_users;
    auto l_ranking = new std::list<User *>;
    try{
        usefulFT::stableSortUsers(tempL, [](User &a, const User& b) {
            return a.getTimeSpent() > b.getTimeSpent();
        });
        for(auto &usr : tempL){
            l_ranking->push_back(usr);
        }

    }catch(runtime_error &ex) {
        cout << ex.what();
        delete l_ranking; /** Clean up to avoid memory leak **/
        logging(error_logfile, __FUNCTION__, ex.what());
        return nullptr;
    }
    return l_ranking;
}


std::list<User *> *Casino::Most_Wins_Users(){

    auto tempL = l_users;
    auto l_ranking = new std::list<User *>;
    try{
        usefulFT::stableSortUsers(tempL, [](User &a, const User& b) {
            return a.getPrizesWon() > b.getPrizesWon();
        });
        for(auto &usr : tempL){
            l_ranking->push_back(usr);
        }

    }catch(runtime_error &ex) {
        cout << ex.what();
        delete l_ranking; /** Clean up to avoid memory leak **/
        logging(error_logfile, __FUNCTION__, ex.what());
        return nullptr;
    }
    return l_ranking;

}


void Casino::Report(const std::string& xml_file){
    try{
        pugi::xml_document doc;

        /** Create a root node for the casino **/
        pugi::xml_node casinoNode = doc.append_child("CASINO");
        casinoNode.append_attribute("NAME") = NAME.c_str();
        casinoNode.append_attribute("JACKPOTRADIUS") = JackpotRadius;

        try{
            usefulFT::stableSortContainer(l_machines, [](const Machine& a, const Machine& b) {
                return a.getUID() < b.getUID();
            });

        }catch(runtime_error &ex) {
            cout << ex.what() << endl;
            logging(error_logfile, __FUNCTION__, ex.what());
        }
        /** Add machines **/
        pugi::xml_node machinesNode = casinoNode.append_child("MACHINES");

        for (const auto &machine: l_machines) {
            pugi::xml_node machineNode = machinesNode.append_child("MACHINE");
            machineNode.append_attribute("ID") = machine->getUID();
            machineNode.append_attribute("TYPE") = machineTypeToString(machine->getType()).c_str();
            machineNode.append_attribute("STATE") = machineSTATEToString(machine->getState()).c_str();
            machineNode.append_attribute("FAILURE_PROBABILITY") = machine->getFailureProbability();
            machineNode.append_attribute("TEMPERATURE") = machine->getTemperature();
            machineNode.append_attribute("X") = machine->getPosition().first;
            machineNode.append_attribute("Y") = machine->getPosition().second;
            machineNode.append_attribute("WIN_PROBABILITY") = machine->getWinProbability();
            machineNode.append_attribute("FAILURES") = machine->getFailures();
            machineNode.append_attribute("USAGE") = machine->getUsage();
        }

        /** Add users **/
        pugi::xml_node usersNode = casinoNode.append_child("USERS");
        for (const auto &user: l_users) {
            pugi::xml_node userNode = usersNode.append_child("USER");
            userNode.append_attribute("ID") = user->getId();
            userNode.append_attribute("NAME") = user->getName().c_str();
            userNode.append_attribute("CITY") = user->getCity().c_str();
            userNode.append_attribute("AGE") = user->getAge();
            userNode.append_attribute("MONEY") = user->getMoney();
            userNode.append_attribute("PRIZES") = user->getPrizesWon();
            userNode.append_attribute("BETS") = user->getBets();
            userNode.append_attribute("PROFIT") = user->getPrizesWon();
            userNode.append_attribute("DEBT") = user->getDebt();
        }

        /** Save the document **/
        doc.save_file(xml_file.c_str());
    } catch (const std::bad_alloc& ex) {
        cout << ex.what() << endl;
        logging(error_logfile, __FUNCTION__, ex.what());
        abort();
    } catch (const std::runtime_error& ex) {
        cout << ex.what() << endl;
        logging(error_logfile, __FUNCTION__, ex.what());
    }
}

float Casino::DistanceBetweenPoints(int first, int second, int first1, int second1) {
    return sqrt(pow(first1 - first, 2) + pow(second1 - second, 2));
}

void Casino::Up_Neighbour_Probability(Machine *M_win, float R, std::list<Machine *> &list_machine_neighbour){
    if (M_win == nullptr) {
        std::cerr << "Winning machine pointer is null.\n";
        return;
    }
    for(Machine* m : list_machine_neighbour){
        /** Ensure the machine pointer is valid and not the winning machine itself **/
        if(m && m != M_win){
            float distance = DistanceBetweenPoints(
                    M_win->getPosition().first, M_win->getPosition().second,
                    m->getPosition().first, m->getPosition().second
            );
            /** Increase win probability if within the radius R **/
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
        auto result = mac->Play(usr);
        if(result) Up_Neighbour_Probability(mac, this->getRadius(), l_machines );
        if(mac->getFailureProbability() == 0.8f) {
            throw runtime_error{"Machine malfunction due to failure in the system hardware."};
        }

    } catch (runtime_error &ex) {
        cerr<<"\nAn error as occurred while trying to use machine\n\t"
            << '[' << mac->getUID() << ']' << " ... -> " << ex.what() << endl;
        logging(error_logfile, "[[EXCEPTION CAUGHT]--[WHILE_TRYING_TO_USE_MACHINE]]", ex.what());
        auto [x,y] = mac->getPosition();
        string s = "[[ {" + to_string(mac->getUID()) +  "},{" +
                machineTypeToString(mac->getType()) + "} at { [" + to_string(x) + "," + to_string(y) + "] }" +
                " with {" + to_string(mac->getTemperature()) + "º Temperature} " + "]]";
        logging(error_logfile, "[[SHUTTING DOWN MACHINE]]", s);
        BrokenMachine(mac->getUID());
    }
    logging(logfile, __FUNCTION__, mac->toString());
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


Machine* Casino::getRandomMachineFromVector(const std::vector<Machine *>& vec) {
    auto machineCount = vec.size();
    int randomIndex = randomNumberGeneratorInterval(0, static_cast<int>(machineCount) - 1);
    auto t = vec.at(randomIndex);
    return t;
}

Machine* Casino::getRandomMachineByType(MACHINE_TYPE type){
    /** Check if there are machines of the given type **/
    Machine* machine= nullptr;
    try{
        switch (type) {
            case MACHINE_TYPE::BLACKJACK:
                if (v_Blackjack_Machines.empty()) { throw runtime_error{"Empty Blackjack List"}; }
                machine = getRandomMachineFromVector(v_Blackjack_Machines);
                break;
            case MACHINE_TYPE::ROULETTE:
                if (v_Roulette_Machines.empty()) { throw runtime_error{"Empty Roulette List"}; }
                machine = getRandomMachineFromVector(v_Roulette_Machines);
                break;
            case MACHINE_TYPE::CLASSIC_SLOT:
                if (v_classicSlots_Machines.empty()) { throw runtime_error{"Empty ClassicSlot List"}; }
                machine = getRandomMachineFromVector(v_classicSlots_Machines);
                break;
            case MACHINE_TYPE::CRAPS:
                if (v_Craps_Machines.empty()) { throw runtime_error{"Empty Craps List"}; }
                machine = getRandomMachineFromVector(v_Craps_Machines);
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
        } else if (state == MACHINE_STATE::MAINTENANCE /*&& ( timeInMaintenance >= 5 )*/ ) {
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

int Casino::getRadius() const{
    return JackpotRadius;
}
