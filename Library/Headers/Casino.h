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

/***********************************************************************************************************************************************
 * Casino ADT class description                                                                                                                *
 *                                                                                                                                             *
 * The Casino class represents a virtual casino environment.                                                                                   *
 * It manages various aspects of a casino, including gaming machines, players, and operational logistics.                                      *
 * This class is a pivotal part of the application, encapsulating all the functionalities and entities related to the casino's operations.     *                                                       *
 *                                                                                                                                             *
 * NAME                -> A string representing the name of the casino.                                                                        *
 *                        This is essential for identification and possibly for UI representation.                                             *
 *                                                                                                                                             *
 * MAX_Players         -> An integer indicating the maximum number of players that the casino can accommodate at any given time.               *
 *                        This is crucial for managing casino capacity.                                                                        *
 *                                                                                                                                             *
 * JackpotRadius       -> An integer representing the radius (possibly in terms of machine proximity) within which a jackpot can be won.       *
 *                        This is a unique feature of the casino, impacting player experience and behavior.                                    *
 *                                                                                                                                             *
 * m_positions         -> A map with pairs of integers (representing X, Y coordinates) as keys and machine IDs (uint16_t) as values.           *
 *                        This map is used to track the physical placement of machines within the casino.                                      *
 *                                                                                                                                             *
 * l_machines          -> A list of pointers to Machine objects. This list holds all machines present in the casino, regardless of their type. *
 *                                                                                                                                             *
 * m_machine_id        -> A map associating machine IDs (uint16_t) with pointers to their corresponding Machine objects.                       *
 *                        This is crucial for the quick identification and access of machines based on their ID.                               *
 *                                                                                                                                             *
 * v_classicSlots_Machines -> A vector of pointers to Machine objects, specifically those representing classic slot machines.                  *
 *                            Vectors are chosen over lists for more efficient random access.                                                  *
 *                                                                                                                                             *
 * v_Blackjack_Machines -> Similar to v_classicSlots_Machines, this vector stores pointers to Blackjack machines in the casino.                *
 *                                                                                                                                             *
 * v_Roulette_Machines -> A vector storing pointers to Roulette machines.                                                                      *
 *                                                                                                                                             *
 * v_Craps_Machines    -> A vector for storing pointers to Craps machines.                                                                     *
 *                                                                                                                                             *
 * l_users             -> A list of pointers to User objects, representing the users or                                                        *
 *                        players currently in the casino.                                                                                     *
 *                                                                                                                                             *
 * v_Broken_Machines   -> A vector of pointers to Machine objects that are currently broken or out of service.                                 *
 *                        This is essential for maintenance and repair management.                                                             *
 *                                                                                                                                             *
 * rolex               -> A pointer to a Clock object (named 'rolex'), used for tracking the operational time of the casino,                   *
 *                      including opening and closing times, or for time-based events within the casino.                                       *
 *                                                                                                                                             *
 ***********************************************************************************************************************************************/

class Casino {
private:
    std::string NAME;
    float JackpotRadius{};
    std::map<std::pair<int, int>, uint16_t > m_positions; // A map with the machines position and the machine ID
    std::list<Machine *> l_machines; // A list with machine TYPE as key and machine list as value
    std::map<uint16_t , Machine*> m_machine_id; // mapping between ID of machine and machine
    std::vector<Machine *> v_classicSlots_Machines; //vectors instead of lists for easier randomized access
    std::vector<Machine *> v_Blackjack_Machines;
    std::vector<Machine *> v_Roulette_Machines;
    std::vector<Machine *> v_Craps_Machines;
    std::list<User*> l_users;
    std::vector<Machine *> v_Broken_Machines;
    unsigned long long total_profits;
    // More data members related to opening and closing time, etc.
    Clock *rolex;

public:
    /********************************************************************************************************************************************************************
     * @brief Constructor for Casino with specified name parameter.                                                                                                     *
     *                                                                                                                                                                  *
     * This constructor initializes a `Casino` instance with a given name. It sets up the casino's name and initializes a new `Clock` instance to manage                *
     * time-related actions within the casino. The constructor also initializes the maximum number of players and the jackpot radius with default values.               *
     *                                                                                                                                                                  *
     * @param name The name of the casino.                                                                                                                              *
     *                                                                                                                                                                  *
     * @exception None. This constructor does not throw exceptions.                                                                                                     *
     * @exceptsafe This constructor is exception-neutral.                                                                                                               *
     * @return None. Constructors do not return values.                                                                                                                 *
     ********************************************************************************************************************************************************************/
    explicit Casino(std::string name);
    /********************************************************************************************************************************************************************
     * @brief Constructor for Casino with specified name, maximum number of players and jackpot radius parameters.                                                      *
     *                                                                                                                                                                  *
     * This constructor initializes a `Casino` instance with a given name, max number of players and jackpot radius.. It sets up the casino's name, max # of players    *
     * and initializes a new `Clock` instance, along with default values for maximum players and jackpot radius.                                                        *
     * @note This constructor was created but never used.                                                                                                               *
     *                                                                                                                                                                  *
     * @param name The name of the casino.                                                                                                                              *
     * @param MAX_Players The number of maximum players for the casino.                                                                                                 *
     * @param JackpotRadius The jackpot radius.                                                                                                                         *
     *                                                                                                                                                                  *
     * @exception None. This constructor does not throw exceptions.                                                                                                     *
     * @exceptsafe This constructor is exception-neutral.                                                                                                               *
     * @return None. Constructors do not return values.                                                                                                                 *
     *******************************************************************************************************************************************************************/
    Casino(std::string name, int MAX_Players, float JackpotRadius);

    /********************************************************************************************************************************************************************
     * @brief Destructor for Casino.                                                                                                                                    *
     *                                                                                                                                                                  *
     * This destructor for the `Casino` class handles the cleanup of dynamically allocated resources. It deletes all user and machine objects stored in the casino's    *
     * lists and clears all internal containers to prevent memory leaks. Additionally, it deletes the `Clock` instance (`rolex`) used for time management.              *
     *                                                                                                                                                                  *
     * @exception None. This destructor does not throw exceptions.                                                                                                      *
     * @exceptsafe This destructor is exception-neutral.                                                                                                                *
     *                                                                                                                                                                  *
     * @return None. Destructors do not return values.                                                                                                                  *
    *********************************************************************************************************************************************************************/
    ~Casino();

    /********************************************************************************************************************************************************************
     * @brief Loads casino data from an XML file.                                                                                                                       *
     *                                                                                                                                                                  *
     * This function loads casino settings and machine details from a specified XML file. It reads casino settings like name, maximum players, jackpot radius, and      *
     * iterates through machine details, creating corresponding `Machine` objects and adding them to the casino. The function logs the loading process and handles      *
     * file reading errors.                                                                                                                                             *
     *                                                                                                                                                                  *
     * @param file The XML file from which to load the casino data.                                                                                                     *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions but reports errors through logging.                                                                     *
     * @exceptsafe This function is exception-neutral.                                                                                                                  *
     *                                                                                                                                                                  *
     * @return bool - `true` if the loading process is successful, `false` otherwise.                                                                                   *
     *******************************************************************************************************************************************************************/
    bool Load(const std::string &file);

    /********************************************************************************************************************************************************************
     * @brief Reads user data from a file and adds users to the casino.                                                                                                 *
     *                                                                                                                                                                  *
     * This function reads user data from a specified file and creates `User` objects based on the data. It adds each new user to the casino, ensuring no duplicate     *
     * users are added based on unique IDs. The function logs the process of reading and adding users, and handles file reading errors.                                 *
     *                                                                                                                                                                  *
     * @note The function assumes a specific file format and structure for user data.                                                                                   *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions but reports errors through logging.                                                                     *
     * @exceptsafe This function is exception-neutral and provides basic exception safety.                                                                              *
     * @return void. This function does not return a value.                                                                                                             *
     *******************************************************************************************************************************************************************/
    void ReadPeopleFile();

    /********************************************************************************************************************
     * @brief Adds a User or Machine to the Casino.                                                                     *
     *                                                                                                                  *
     * These functions adds a `User` to the casino. It sets an initial money value and adds the user to the user list.  *
     *                                                                                                                  *
     * @param usr A pointer to the `User` object to be added.                                                           *
     *                                                                                                                  *
     * @exception None. These functions do not throw exceptions but report errors through logging.                      *
     * @exceptsafe These functions are exception-neutral.                                                               *
     *                                                                                                                  *
     * @return bool - `true` if the addition is successful, `false` otherwise.                                          *
     ********************************************************************************************************************/
    bool Add(User *usr);

    /********************************************************************************************************************************************************************
     * @brief Adds a Machine to the Casino.                                                                                                                             *
     *                                                                                                                                                                  *
     * This function attempts to add a `Machine` object to the casino. It first checks if the machine pointer is null and the position availability. If the position    *
     * is available and the machine is valid, it adds the machine to the casino's database and returns true. If the position is already taken, it returns false.        *
     *                                                                                                                                                                  *
     * @param m Pointer to the `Machine` object to be added.                                                                                                            *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions but logs errors.                                                                                        *
     * @exceptsafe This function is exception-neutral and provides basic exception safety.                                                                              *
     *                                                                                                                                                                  *
     * @return bool - `true` if the machine is successfully added, `false` otherwise.                                                                                   *
     ********************************************************************************************************************************************************************/
    bool Add(Machine *m);

    /********************************************************************************************************************************************************************
     * @brief Checks if a machine position is available in the Casino.                                                                                                  *
     *                                                                                                                                                                  *
     * This function checks whether a specified position is already occupied by a machine in the casino. It iterates through the positions of existing machines and     *
     * compares them with the given position.                                                                                                                           *
     *                                                                                                                                                                  *
     * @param position A pair of integers representing the x and y coordinates of the machine's position.                                                               *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any program state.                                                                            *
     *                                                                                                                                                                  *
     * @return bool - `true` if the position is available, `false` if it is already occupied.                                                                           *
     ********************************************************************************************************************************************************************/
    bool checkMachinePositionAvailability(pair<int,int> position);

    /********************************************************************************************************************************************************************
     * @brief Adds a machine to the casino's database.                                                                                                                  *
     *                                                                                                                                                                  *
     * This function adds a machine to the casino's internal data structures, including lists and maps that categorize machines by type and track their positions       *
     * and IDs. It checks for duplicate IDs and only adds the machine if it's unique.                                                                                   *
     *                                                                                                                                                                  *
     * @param m Pointer to the `Machine` object to be added.                                                                                                            *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions but logs errors.                                                                                        *
     * @exceptsafe This function is exception-neutral and provides basic exception safety.                                                                              *
     *                                                                                                                                                                  *
     * @return void. This function does not return a value but updates the casino's internal data structures.                                                           *
     ********************************************************************************************************************************************************************/
    void databaseAddMachine(Machine *m);


    /********************************************************************************************************************************************************************
     * @brief Lists machines and/or users in the casino.                                                                                                                *
     *                                                                                                                                                                  *
     * These overloaded functions provide listings of machines and users in the casino. One version lists all machines without ordering, while the other lists          *
     * machines with a winning odd higher than a specified value. Both functions output the listings to a provided `std::ostream`.                                      *
     *                                                                                                                                                                  *
     * @param f A reference to an `std::ostream` for output.                                                                                                            *
     * @param X A float value specifying the threshold for winning odds in the second version.                                                                          *
     *                                                                                                                                                                  *
     * @exception None. These functions do not throw exceptions.                                                                                                        *
     * @exceptsafe These functions are exception-neutral and do not modify any program state.                                                                           *
     *                                                                                                                                                                  *
     * @return void. These functions do not return values but output to the provided stream.                                                                            *
     ********************************************************************************************************************************************************************/
    void Listing(std::ostream &f = std::cout);
    void Listing(float X, std::ostream &f = std::cout);

    /********************************************************************************************************************************************************************
     * @brief Lists machine IDs in the casino.                                                                                                                          *
     *                                                                                                                                                                  *
     * This function lists the unique IDs of all machines in the casino. It outputs the list to a provided `std::ostream`, enhancing readability with a decorative      *
     * border.                                                                                                                                                          *
     *                                                                                                                                                                  *
     * @param f A reference to an `std::ostream` for output.                                                                                                            *
     *                                                                                                                                                                  *
     * @exception None. These functions do not throw exceptions.                                                                                                        *
     * @exceptsafe These functions are exception-neutral and do not modify any program state.                                                                           *
     *                                                                                                                                                                  *
     * @return void. These functions do not return values but output to the provided stream.                                                                            *
     ********************************************************************************************************************************************************************/
    void ListMachinesUID(std::ostream &f = std::cout);

    /********************************************************************************************************************************************************************
     * @brief Turns off a machine in the casino.                                                                                                                        *
     *                                                                                                                                                                  *
     * This function turns off a machine with a specified ID in the casino. If the machine ID is found, the machine's state is set to `OFF`. If the ID is not found,    *
     * an appropriate message is displayed.                                                                                                                             *
     *                                                                                                                                                                  *
     * @param id_mac The ID of the machine to be turned off.                                                                                                            *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any program state other than the machine's state.                                             *
     * @return void. This function does not return a value.                                                                                                             *
     ********************************************************************************************************************************************************************/
    void TurnOff(int id_mac);

    /********************************************************************************************************************************************************************
     * @brief Marks a machine in the casino as broken.                                                                                                                  *
     *                                                                                                                                                                  *
     * This function sets the state of a machine with a specified ID to `BROKEN`. If the machine ID is found, it is also added to the list of broken machines.          *
     * If the ID is not found, an appropriate message is displayed.                                                                                                     *
     *                                                                                                                                                                  *
     * @param id_mac The ID of the machine to be marked as broken.                                                                                                      *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any program state other than the machine's state.                                             *
     *                                                                                                                                                                  *
     * @return void. This function does not return a value.                                                                                                             *
     ********************************************************************************************************************************************************************/
    void BrokenMachine(int id_mac);

    /********************************************************************************************************************************************************************
     * @brief Retrieves the state of a specified machine in the Casino.                                                                                                 *
     *                                                                                                                                                                  *
     * This function returns the state of a machine identified by its ID. If the machine is not found, it throws and logs a runtime error and returns a                 *
     * `NONEXISTENT` state.                                                                                                                                             *
     *                                                                                                                                                                  *
     * @param id_mac The ID of the machine whose state is to be retrieved.                                                                                              *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if the machine is not found.                                                                                                     *
     * @exceptsafe This function provides strong exception safety.                                                                                                      *
     *                                                                                                                                                                  *
     * @return MACHINE_STATE - The state of the machine, or `MACHINE_STATE::NONEXISTENT` if the machine is not found.                                                   *
     ********************************************************************************************************************************************************************/
    MACHINE_STATE getState(int id_mac);

    /********************************************************************************************************************************************************************
     * @brief Retrieves the casino's clock.                                                                                                                             *
     *                                                                                                                                                                  *
     * This function returns a pointer to the `Clock` object associated with the casino. This clock is used for managing and tracking time-related events within the    *
     * casino.                                                                                                                                                          *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any program state.                                                                            *
     *                                                                                                                                                                  *
     * @return Clock* - A pointer to the casino's `Clock` object.                                                                                                       *
     *******************************************************************************************************************************************************************/
    [[nodiscard]] Clock* getClock() const;


    /********************************************************************************************************************************************************************
     * @brief Calculates the total memory used by the Casino object.                                                                                                    *
     *                                                                                                                                                                  *
     * This function computes the total memory used by the `Casino` object, including all its data members. It considers the memory used by the `Casino` object         *
     * itself, all machines, users, and internal data structures like lists and maps. This is useful for analyzing the memory footprint of the casino.                  *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any program state.                                                                            *
     *                                                                                                                                                                  *
     * @return size_t - The total memory used by the `Casino` object in bytes.                                                                                          *
     ********************************************************************************************************************************************************************/
    [[nodiscard]] size_t Total_Memory() const;

    /********************************************************************************************************************************************************************
     * @brief Lists machines of a specific type in the Casino.                                                                                                          *
     *                                                                                                                                                                  *
     * This function creates a list of machines of a specified type. It throws an exception if the list for the specified type is empty. The function logs errors       *
     * and performs cleanup to avoid memory leaks in case of exceptions.                                                                                                *
     *                                                                                                                                                                  *
     * @param Type The type of machines to list.                                                                                                                        *
     * @param f Reference to an `std::ostream` for error logging.                                                                                                       *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if the list of the specified type is empty.                                                                                      *
     * @exceptsafe This function provides strong exception safety.                                                                                                      *
     *                                                                                                                                                                  *
     * @return std::list<Machine *> * - Pointer to a list of machines of the specified type.                                                                            *
     *******************************************************************************************************************************************************************/
    std::list<Machine *> *List_Types(MACHINE_TYPE Type, std::ostream &f = std::cout);

    /********************************************************************************************************************************************************************
     * @brief Ranks machines based on the number of failures.                                                                                                           *
     *                                                                                                                                                                  *
     * This function ranks the machines in the casino based on the number of failures (from highest to lowest). It returns a list of machine information in the         *
     * sorted order. The function handles exceptions and performs necessary cleanup.                                                                                    *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if any error occurs during sorting.                                                                                              *
     * @exceptsafe This function provides strong exception safety.                                                                                                      *
     *                                                                                                                                                                  *
     * @return std::list<std::string> * - Pointer to a list containing machine information sorted by the number of failures.                                            *
     ********************************************************************************************************************************************************************/
    std::list<std::string> *Ranking_of_the_weaks();

    /********************************************************************************************************************************************************************
     * @brief Ranks machines based on usage.                                                                                                                            *
     *                                                                                                                                                                  *
     * This function creates a list of machines ranked based on their usage (from highest to lowest). It handles exceptions and performs necessary cleanup to avoid     *
     * memory leaks.                                                                                                                                                    *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if any error occurs during sorting.                                                                                              *
     * @exceptsafe This function provides strong exception safety.                                                                                                      *
     *                                                                                                                                                                  *
     * @return std::list<Machine *> * - Pointer to a list of machines sorted by usage.                                                                                  *
     ********************************************************************************************************************************************************************/
    std::list<Machine *> *Ranking_of_the_most_used();

    /********************************************************************************************************************************************************************
     * @brief Ranks users based on time spent in the Casino.                                                                                                            *
     *                                                                                                                                                                  *
     * This function ranks the users based on the time they have spent in the casino. It returns a list of users in the sorted order. The function handles              *
     * exceptions and performs cleanup to avoid memory leaks.                                                                                                           *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if any error occurs during sorting.                                                                                              *
     * @exceptsafe This function provides strong exception safety.                                                                                                      *
     *                                                                                                                                                                  *
     * @return std::list<User *> * - Pointer to a list of users sorted by time spent.                                                                                   *
     ********************************************************************************************************************************************************************/
    std::list<User *> *Most_Frequent_Users();

    /********************************************************************************************************************************************************************
     * @brief Ranks users based on the amount of prizes won.                                                                                                            *
     *                                                                                                                                                                  *
     * This function creates a list of users ranked based on the total amount of prizes they have won. It handles exceptions and performs necessary cleanup to          *
     * avoid memory leaks.                                                                                                                                              *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if any error occurs during sorting.                                                                                              *
     * @exceptsafe This function provides strong exception safety.                                                                                                      *
     *                                                                                                                                                                  *
     * @return std::list<User *> * - Pointer to a list of users sorted by the amount of prizes won.                                                                     *
     ********************************************************************************************************************************************************************/
    std::list<User *> *Most_Wins_Users();

    /********************************************************************************************************************************************************************
     * @brief Generates a report of the casino's current state and saves it as an XML file.                                                                             *
     *                                                                                                                                                                  *
     * This function creates a comprehensive XML report of the current state of the casino, including details about its machines and users. The report includes         *
     * attributes such as machine ID, type, state, failure probability, and more. For users, attributes like ID, name, city, age, money, and others are included.       *
     * It saves the report to the specified XML file.                                                                                                                   *
     *                                                                                                                                                                  *
     * @param xml_file The name of the XML file to which the report will be saved.                                                                                      *
     *                                                                                                                                                                  *
     * @exception bad_alloc Thrown if memory allocation fails during XML creation.                                                                                      *
     * @exception runtime_error Thrown if any runtime error occurs during the process.                                                                                  *
     * @exceptsafe This function provides basic exception safety.                                                                                                       *
     *                                                                                                                                                                  *
     * @return void. This function does not return a value but outputs the casino state to an XML file.                                                                 *
     ********************************************************************************************************************************************************************/
    void Report(const std::string &xml_file);

    /********************************************************************************************************************************************************************
     * @brief Calculates the distance between two points.                                                                                                               *
     *                                                                                                                                                                  *
     * This function computes the Euclidean distance between two points in a 2D space. Each point is represented by a pair of integers (x, y coordinates).              *
     *                                                                                                                                                                  *
     * @param first The x-coordinate of the first point.                                                                                                                *
     * @param second The y-coordinate of the first point.                                                                                                               *
     * @param first1 The x-coordinate of the second point.                                                                                                              *
     * @param second1 The y-coordinate of the second point.                                                                                                             *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any program state.                                                                            *
     *                                                                                                                                                                  *
     * @return float - The Euclidean distance between the two points.                                                                                                   *
     ********************************************************************************************************************************************************************/
    static float DistanceBetweenPoints(int first, int second, int first1, int second1);

    /********************************************************************************************************************************************************************
     * @brief Increases the win probability of machines in the vicinity of a winning machine.                                                                           *
     *                                                                                                                                                                  *
     * This function increases the win probability of machines located within a certain radius (R) from a winning machine (M_win). It iterates through a list of        *
     * machines, checks if each machine is within the specified radius from the winning machine, and increases its win probability if it is.                            *
     *                                                                                                                                                                  *
     * @param M_win Pointer to the winning machine.                                                                                                                     *
     * @param R The radius within which the win probability of neighboring machines is to be increased.                                                                 *
     * @param list_machine_neighbour A list of machines to be considered for the win probability increase.                                                              *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions but checks for null pointers.                                                                           *
     * @exceptsafe This function is exception-neutral and provides basic exception safety.                                                                              *
     *                                                                                                                                                                  *
     * @return void. This function does not return a value but modifies the win probability of certain machines.                                                        *
     ********************************************************************************************************************************************************************/
    static void Up_Neighbour_Probability(Machine *M_win, float R, std::list<Machine *> &list_machine_neighbour);




    /********************************************************************************************************************************************************************
     * @brief Executes the main operational logic of the Casino.                                                                                                        *
     *                                                                                                                                                                  *
     * Initiates the casino's operation by selecting a random user and assigning them to a working machine (not broken or off). It conducts various checks such as      *
     * ensuring the machine is operational and within acceptable temperature limits. If a machine malfunctions due to high temperature or hardware failure,             *
     * appropriate actions are taken, including logging the incident and setting the machine's status to 'broken'.                                                      *
     *                                                                                                                                                                  *
     * @see getRandomUser() for selecting a random user.                                                                                                                *
     * @see getRandomType() for selecting a random machine type.                                                                                                        *
     * @see getRandomMachineByType() for selecting a random machine by type.                                                                                            *
     * @see Machine::Play() for simulating machine play.                                                                                                                *
     * @see Up_Neighbour_Probability() for increasing win probability of nearby machines.                                                                               *
     * @see logging() for logging errors and information.                                                                                                               *
     * @see Machine and User class for extra information on less relevant method used.                                                                                  *                                                                                                                                                                  *
     * @exception runtime_error Thrown if an error occurs during machine operation.                                                                                     *
     * @exceptsafe Strong exception safety is guaranteed. State modifications occur only if operations are successful.                                                  *
     *                                                                                                                                                                  *
     * @return void. No return value but executes a series of operations simulating casino activity.                                                                    *
     ********************************************************************************************************************************************************************/
    void Run();

    /********************************************************************************************************************************************************************
     * @brief Conducts routine checks and maintenance on the casino's machines.                                                                                         *
     *                                                                                                                                                                  *
     * Iterates through the list of broken machines, performing maintenance tasks. Machines that have been repaired are reactivated and returned to the operational     *
     * pool. The function tracks the time each machine spends in maintenance and logs activities accordingly.                                                           *
     *                                                                                                                                                                  *
     * @see removeFromTypeVector() for removing a machine from its specific type vector during maintenance.                                                             *
     * @see addToTypeVector() for re-adding a machine to its type vector after maintenance.                                                                             *
     * @see logging() for logging maintenance activities.                                                                                                               *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe Strong exception safety. State changes occur only if operations are successful.                                                                      *
     *                                                                                                                                                                  *
     * @return void. No return value but performs maintenance on machines and updates their states.                                                                     *
     ********************************************************************************************************************************************************************/
    void check_routine();

    /********************************************************************************************************************************************************************
     * @brief Selects a random user from the list of users in the Casino.                                                                                               *
     *                                                                                                                                                                  *
     * Chooses a random user from the casino's user list. If the list is empty, it returns a null pointer. The function generates a random index and uses it to         *
     * fetch a user from the list.                                                                                                                                      *
     *                                                                                                                                                                  *
     * @see randomNumberGeneratorInterval() for generating a random index.                                                                                              *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe Exception-neutral with no state change in case of failure.                                                                                           *
     *                                                                                                                                                                  *
     * @return User* - A pointer to a randomly selected user or nullptr if the list is empty.                                                                           *
     ********************************************************************************************************************************************************************/
    User* getRandomUser();

    /********************************************************************************************************************************************************************
     * @brief Selects a random machine of a specified type from the Casino.                                                                                             *
     *                                                                                                                                                                  *
     * Fetches a random machine of the specified type from the casino. It checks the availability of machines of that type and selects one at random. If no machines    *
     * are available for the specified type, it logs an error and returns a null pointer.                                                                               *
     *                                                                                                                                                                  *
     * @see getRandomMachineFromVector() for selecting a machine from a vector.                                                                                         *
     * @see logging() for error logging.                                                                                                                                *
     *                                                                                                                                                                  *
     * @param type The type of machine to be selected.                                                                                                                  *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if no machines of the specified type are available.                                                                              *
     * @exceptsafe Strong exception safety is provided. Returns null without changing state if an error occurs.                                                         *
     *                                                                                                                                                                  *
     * @return Machine* - A pointer to a randomly selected machine of the specified type, or nullptr if unavailable.                                                    *
     ********************************************************************************************************************************************************************/
    Machine* getRandomMachineByType(MACHINE_TYPE type);

    /********************************************************************************************************************************************************************
     * @brief Randomly selects a machine from a given vector of machines.                                                                                               *
     *                                                                                                                                                                  *
     * This function selects and returns a random `Machine` object from a provided vector of machines. It calculates the size of the vector, generates a random index   *
     * within the bounds of the vector, and then returns the machine at that index. This method is used when a random machine needs to be chosen from a specific        *
     * subset of machines, typically categorized by type.                                                                                                               *
     *                                                                                                                                                                  *
     * @param vec A constant reference to a vector of `Machine` pointers, representing a specific subset of machines.                                                   *
     *                                                                                                                                                                  *
     * @see randomNumberGeneratorInterval() for generating the random index within the range of the vector size.                                                        *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions, but it returns `nullptr` if the vector is empty.                                                       *
     * @exceptsafe This function is exception-neutral and does not modify any program state.                                                                            *
     *                                                                                                                                                                  *
     * @return Machine* - A pointer to the randomly selected machine from the vector. Returns `nullptr` if the vector is empty.                                         *
     *******************************************************************************************************************************************************************/
    static Machine* getRandomMachineFromVector(const std::vector<Machine *>& vec);

    /********************************************************************************************************************************************************************
     * @brief Randomly selects a type of machine currently in use in the Casino.                                                                                        *
     *                                                                                                                                                                  *
     * This function returns a random `MACHINE_TYPE` from a predefined array of machine types currently in use. It randomly selects an index within the range of        *
     * the array and returns the machine type at that index. This method is typically used to randomly choose a type of machine for various casino operations.          *
     *                                                                                                                                                                  *
     * @see randomNumberGeneratorInterval() for generating the random index within the range of available machine types.                                                *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any program state.                                                                            *
     *                                                                                                                                                                  *
     * @return MACHINE_TYPE - A randomly selected machine type from the types currently in use.                                                                         *
     ********************************************************************************************************************************************************************/
    static MACHINE_TYPE getRandomType();

    /********************************************************************************************************************************************************************
     * @brief Modifies the failure probability of a randomly selected machine.                                                                                          *
     *                                                                                                                                                                  *
     * Randomly selects a machine and sets its failure probability to a high value (80%). This simulates a scenario where a machine becomes more likely to fail,        *
     * either due to wear and tear or other factors.                                                                                                                    *
     *                                                                                                                                                                  *
     * @see getRandomMachineByType() for selecting a random machine.                                                                                                    *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe Exception-neutral with state changes confined to the selected machine.                                                                               *
     *                                                                                                                                                                  *
     * @return void. No return value, but modifies the failure probability of a selected machine.                                                                       *
     ********************************************************************************************************************************************************************/
    void changeMachineFailProbability();

    /********************************************************************************************************************************************************************
     * @brief Increases the winning odds of a randomly selected machine.                                                                                                *
     *                                                                                                                                                                  *
     * Enhances the winning probability of a randomly chosen machine by a significant margin (15%). This represents an adjustment in the machine's settings to          *
     * potentially offer more frequent payouts.                                                                                                                         *
     *                                                                                                                                                                  *
     * @see getRandomMachineByType() for selecting a random machine.                                                                                                    *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe Exception-neutral with state changes confined to the selected machine.                                                                               *
     *                                                                                                                                                                  *
     * @return void. No return value but alters the win probability of a chosen machine.                                                                                *
    *********************************************************************************************************************************************************************/
    void RandomOddImprovement();

    /********************************************************************************************************************************************************************
     * @brief Removes a machine from its respective type vector in the Casino.                                                                                          *
     *                                                                                                                                                                  *
     * This function removes a specified machine from the vector corresponding to its type. It identifies the correct vector based on the machine type and removes      *
     * the machine from it. This is typically used when a machine is undergoing maintenance or is otherwise taken out of service.                                       *
     *                                                                                                                                                                  *
     * @param machine Pointer to the `Machine` object to be removed.                                                                                                    *
     * @param type The type of the machine which determines the vector it is stored in.                                                                                 *
     *                                                                                                                                                                  *
     * @see logging() for logging if an error occurs.                                                                                                                   *
     *                                                                                                                                                                  *
     * @exception runtime_error Thrown if the vector for the specified type is empty.                                                                                   *
     * @exceptsafe Provides strong exception safety. If an error occurs, no changes are made to the state.                                                              *
     *                                                                                                                                                                  *
     * @return void. No return value but modifies the vector of machines of the specified type.                                                                         *
     ********************************************************************************************************************************************************************/
    void removeFromTypeVector(Machine* machine, MACHINE_TYPE type);

    /********************************************************************************************************************************************************************
     * @brief Adds a machine to its respective type vector in the Casino.                                                                                               *
     *                                                                                                                                                                  *
     * This function adds a specified machine to the vector corresponding to its type. This is typically used when a machine is reactivated after maintenance or        *
     * is otherwise put back into service. The function identifies the appropriate vector based on the machine's type and adds the machine to it.                       *
     *                                                                                                                                                                  *
     * @param machine Pointer to the `Machine` object to be added.                                                                                                      *
     * @param type The type of the machine which determines the vector it should be stored in.                                                                          *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe Exception-neutral and does not modify the state if the machine cannot be added.                                                                      *
     *                                                                                                                                                                  *
     * @return void. No return value but modifies the vector of machines of the specified type.                                                                         *
     ********************************************************************************************************************************************************************/
    void addToTypeVector(Machine* machine, MACHINE_TYPE type);

    /********************************************************************************************************************************************************************
     * @brief Prints the sizes of the various machine vectors in the Casino.                                                                                            *
     *                                                                                                                                                                  *
     * This function outputs the sizes of different vectors holding machines of various types, including Blackjack, Craps, Classic Slot, Roulette, and Broken Machines. *
     * It is used for informational purposes, such as monitoring the distribution and availability of machines in the casino.                                           *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe Exception-neutral with no state changes.                                                                                                             *
     *                                                                                                                                                                  *
     * @return void. No return value but prints information to the standard output.                                                                                     *
     ********************************************************************************************************************************************************************/
    void printVectorsSize();

    /********************************************************************************************************************************************************************
     * @brief Returns a string representation of the sizes of various machine vectors in the Casino.                                                                    *
     *                                                                                                                                                                  *
     * Constructs and returns a string detailing the sizes of different vectors holding machines of various types. This includes Blackjack, Craps, Classic Slot,        *
     * Roulette, and Broken Machines. Useful for generating reports or logs that require a summary of the machine distribution in the casino.                           *
     *                                                                                                                                                                  *
     * @exception None. This function does not throw exceptions.                                                                                                        *
     * @exceptsafe Exception-neutral with no state changes.                                                                                                             *
     *                                                                                                                                                                  *
     * @return string - A string containing the sizes of various machine vectors.                                                                                       *
     ********************************************************************************************************************************************************************/
    string VectorsSize();

    /***************************************************
     * @brief Getter for casino jackpot radius         *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return None                                    *
     ***************************************************/
    [[nodiscard]] int getRadius() const;

    /***************************************************
     * @brief Setter for casino total profit           *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return None                                    *
     ***************************************************/
    [[maybe_unused]] void setTotalProfits(unsigned long long totalProfits);

    /***************************************************
     * @brief Add casino profit to casino              *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return None                                    *
     ***************************************************/
    void AddProfits(double profits);

    /***************************************************
     * @brief Getter for casino total profit           *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return None                                    *
     ***************************************************/
    [[nodiscard]] unsigned long long getTotalProfits() const;
};

#endif //CODE_CASINO_H
