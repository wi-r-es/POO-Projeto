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

#include "Machine.h"
#include "Classic_Slot.h"
#include "Craps.h"
#include "Blackjack.h"
#include "Roulette.h"


#include "User.h"

#include <list>  // user vector instead of LIST ?
#include <string>
#include <map>


/****************************************************************************************************************************
 * Casino ADT class and variables description                                                                               *
 * @see Machines                                                                                                            *
 * @see Users                                                                                                               *
 *                                                                                                                          *
 * NAME                      -> String representing the name of the casino.                                                 *
 * m_machines                -> Map of the machines inside the casino. (MachineType, List of machines of that type).        *
 * l_classicSlots_Machines   -> List of Classic slots Machines.                                                             *
 * l_Blackjack_Machines      -> List of Blackjack Machines.                                                                 *
 * l_Roulette_Machines       -> List of Roulette Machines.                                                                  *
 * l_Craps_Machines          -> List of Craps Machines.                                                                     *
 * l_users                   -> List of Users/clients.                                                                      *
 ****************************************************************************************************************************/

class Casino {
private:
    std::string NAME;
    std::map<MACHINE_TYPE, std::list<Machine *>> m_machines; // A map with machine TYPE as key and machine list as value
    std::list<Machine *> l_classicSlots_Machines;
    std::list<Machine *> l_Blackjack_Machines;
    std::list<Machine *> l_Roulette_Machines;
    std::list<Machine *> l_Craps_Machines;
    std::list<User*> l_users;
    // More data members related to opening and closing time, etc.

public:
    /*****************************************************************
     * @brief Constructor for Casino                                 *
     *                                                               *
     * @param name -> a string representing the name of the Casino.  *
     *****************************************************************/
    explicit Casino(std::string name);
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

    /**********************************
     * @brief Add user to the casino  *
     * @param usr                     *
     * @return                        *
     **********************************/
    bool Add(User *usr);

    /*************************************
     * @brief Add Machine to the casino  *
     * @param m                          *
     * @return                           *
     *************************************/
    bool Add(Machine *m);

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

    /*********************************************************************
     * @brief Getter for the Machine current state, based on given ID    *
     * @param id_mac                                                     *
     * @return Machine current state.                                    *
     *********************************************************************/
    MACHINE_STATE getState(int id_mac);

    /*********************************************************
     * @brief Calculates the total memory occupied by ADTs   *
     * @return Integer representing total memory usage.      *
     *********************************************************/
    int Total_Memory();

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
     * @param Debug : boolean that represents if the has to debug or not.             *
     **********************************************************************************/
    virtual void Run(bool Debug = true);


};
//MACHINES ( MAC1 MACH2 MACH3 MACH4 MACH5 MACH6 MACH7 MAC8
  //      Machine

 // Machine mac1 = new ClassicSlot;
  // Machine mac2 = new Rollete;

/* POO explanation
 * estaticamente mac1 = machine
    dinamicamente mac2 = classicslot
    mac1.runSlot()
    mac2.runRollete()
    versus
    mac1.run()
    mac2.run()
 */
#endif //CODE_CASINO_H
