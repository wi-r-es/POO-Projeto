//
// Created on 06/11/23.
//
/*********************************************************************************
 *  @file Casino.h                                                               *
 *  @brief Class prototypes for Casino ADT Structure/Class                       *
 *                                                                               *
 *  This contains the prototypes for the managing of Casino and its fields.      *
 *                                                                               *
 *********************************************************************************/
#ifndef CODE_CASINO_H
#define CODE_CASINO_H

/******************
 * Headers Files  *
 ******************/
#include "Machine.h"
#include "Classic_Slot.h"
#include "Craps.h"
#include "Blackjack.h"
#include "Roulette.h"
#include "IO.h"
#include "Clock.h"
#include "utils.h"
#include "User.h"

/**********************
 * Libraries Includes *
 **********************/
#include <list>  // user vector instead of LIST ?
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>



extern std::string logfile;
extern std::string error_logfile;

/****************************************************************************************************************************
 * Casino ADT class and variables description                                                                               *
 * @see Machines                                                                                                            *
 * @see Users                                                                                                               *
 *                                                                                                                          *
 * NAME                      -> String representing the name of the casino.                                                 *
 * m_positions
 * m_machine_id
 * m_machines                -> Map of the machines inside the casino. (MachineType, List of machines of that type).        *
 * v_classicSlots_Machines   -> List of Classic slots Machines.                                                             *
 * v_Blackjack_Machines      -> List of Blackjack Machines.                                                                 *
 * v_Roulette_Machines       -> List of Roulette Machines.                                                                  *
 * v_Craps_Machines          -> List of Craps Machines.                                                                     *
 * l_users                   -> List of Users/clients.                                                                      *
 ****************************************************************************************************************************/

class Casino {
private:
    std::string NAME;
    int MAX_Players{};
    int JackpotRadius{};
    std::map<std::pair<int, int>, uint16_t > m_positions; // A map with the machines position and the machine ID
    std::map<MACHINE_TYPE, std::list<Machine *>> m_machines; // A map with machine TYPE as key and machine list as value
    std::map<uint16_t , Machine*> m_machine_id; // mapping between ID of machine and machine
    std::vector<Machine *> v_classicSlots_Machines; //vectors instead of lists for easier randomized access
    std::vector<Machine *> v_Blackjack_Machines;
    std::vector<Machine *> v_Roulette_Machines;
    std::vector<Machine *> v_Craps_Machines;
    std::list<User*> l_users;
    std::vector<Machine *> v_Broken_Machines;
    // More data members related to opening and closing time, etc.
    Clock *rolex;

public:
    /*****************************************************************
     * @brief Constructor for Casino                                 *
     *                                                               *
     * @param name -> a string representing the name of the Casino.  *
     *****************************************************************/
    explicit Casino(std::string name);
    explicit Casino(std::string name, int MAX_Players, int JackpotRadius);
    /***********************************
     * @brief Destructor for Casino    *
     ***********************************/
    virtual ~Casino();

    /**************************************************
     * @brief Load casino configurations from a file  *
     * @param file                                    *
     * @return                                        *
     **************************************************/
    bool Load(const std::string &file);

    /****************************************************************************************************************
     * @brief Read the TXT file of the people randomly generate the n amount of people and put it in the people list *
     * @param n                                                                                                      *
     *****************************************************************************************************************/
    void ReadPeopleFile();

    /**********************************
     * @brief Add user to the casino  *
     * @param usr                     *
     * @return                        *
     **********************************/
    [[maybe_unused]] bool Add(User *usr);

    /*************************************
     * @brief Add Machine to the casino  *
     * @param m                          *
     * @return                           *
     *************************************/
    bool Add(Machine *m);

    /*************************************
     * @brief Checks if a pair position is already filled *
     * @param position                          *
     * @return False if given position is filled, True if position is available.                         *
     *************************************/
    bool checkMachinePositionAvailability(pair<int,int> position);

    void databaseAddMachine(Machine *m);
    /************************************************
     * @brief List the current state of the casino  *
     * @param f                                     *
     ************************************************/
    void Listing(std::ostream &f = std::cout);

    /*************************************************************************
     * @brief Lists the machines which winning percentage is higher than X   *
     * @param X                                                              *
     * @param f                                                              *
     *************************************************************************/
    void Listing(float X, std::ostream &f = std::cout);

    /************************************************
     * @brief Turns off a Machine given its ID      *
     * @param id_mac -> UID of the Machine.         *
     ************************************************/
    void TurnOff(int id_mac);

    void BrokenMachine(int id_mac);

    /*********************************************************************
     * @brief Getter for the Machine current state, based on given ID    *
     * @param id_mac                                                     *
     * @return Machine current state.                                    *
     *********************************************************************/
    MACHINE_STATE getState(int id_mac);

    [[nodiscard]] Clock* getClock() const;


    /*********************************************************
     * @brief Calculates the total memory occupied by ADTs   *
     * @return Integer representing total memory usage.      *
     *********************************************************/
    [[nodiscard]] size_t Total_Memory() const;

    /***************************************************
     * @brief Lists all Machines of a given type.      *
     * @param Type                                     *
     * @param f                                        *
     * @return                                         *
     ***************************************************/
    std::list<Machine *> *List_Types(const std::string& Type, std::ostream &f = std::cout);

    /**************************************************************************************
     * @brief Lists Ranking of the Machines showing the ones who fail more at the top.    *
     * @return                                                                            *
     **************************************************************************************/
    std::list<std::string> *Ranking_of_the_weaks();

    /****************************************************
     * @brief Lists Ranking of the most used Machines   *
     * @return                                          *
     ****************************************************/
    std::list<Machine *> *Ranking_of_the_most_used();

    /*********************************************************************
     * @brief Lists Ranking of the most frequent users at the casino.  *
     * @return                                                           *
     *********************************************************************/
    std::list<User *> *Most_Frequent_Users();

    /**********************************************************
     * @brief Lists Ranking of the users with the most wins.  *
     * @return                                                *
     **********************************************************/
    std::list<User *> *Most_Wins_Users();

    /*******************************************************************************
     * @brief Saves to a XML file the state of the casino and ALL it's machines    *
     * @param xml_file                                                             *
     *******************************************************************************/
    void Report(const std::string &xml_file);

    float DistanceBetweenPoints(int first, int second, int first1, int second1);

    /**************************************************************************************
     * @brief Raises the winning probability of the Machines near                         *
     * @param M_win                                                                       *
     * @param R                                                                           *
     * @param list_machine_neighbour                                                      *
     **************************************************************************************/
    void Up_Neighbour_Probability(Machine *M_win, float R, std::list<Machine *> &list_machine_neighbour);




    /**********************************************************************************
     * @brief Main loop that simulates the operation of the Casino .                  *
     *                                                                                *
     *
     * @see
     **********************************************************************************/
    void Run();
    void check_routine();
    void removeFromTypeVector(Machine* machine, MACHINE_TYPE type);
    void addToTypeVector(Machine* machine, MACHINE_TYPE type);
    User* getRandomUser();
    Machine* getRandomMachineByType(MACHINE_TYPE type);
    MACHINE_TYPE getRandomType();
    void changeMachineFailProbability();
    void RandomOddImprovement();
    void printVectorsSize();
    string VectorsSize();
};

#endif //CODE_CASINO_H
