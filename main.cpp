#include <iostream>

#include "Library/Headers/Casino.h"
#include "Library/Headers/kbhitmodule.h"
#include "Library/Headers/utils.h"

#if defined(_WIN32) || defined(_WIN64)
void clear(){system("cls");}
#else
void clear(){system("clear");} /// Function to clear the screen
#endif

// All documentation at the end of the file, at functions implementation.
void logAtExit();
static string exit_message;
extern string casinoFile;
extern string reportfile;

void SimulateCasino( Casino *casino, u_int8_t &flag);
void Shutdown(Casino *casino);
void menu(Casino* casino);
void submenu(Casino* casino);
void subsubmenu(Casino* casino);
void listingToFile(Casino* casino);
void ROTW(Casino* casino);
void ROTMU(Casino* casino);
void MFU(Casino* casino);
void MWU(Casino* casino);

int main() {
    logging(logfile, __FUNCTION__ , "Starting Program");
    auto startTime = chrono::steady_clock::now();
    Casino *casino = new Casino("Casino_name");
    if( casino->Load("../Files/I/CasinoInfo.xml") ) {
        beautify(" Loaded successful ");
        logging(logfile, __FUNCTION__ , "Casino Loaded Successfully");
    }
    casino->ReadPeopleFile();
    casino->Listing();

    Clock *ptrClock = casino->getClock();
    ptrClock->StartClock(50, "10:00:00");
    u_int8_t flag = 0;
    auto lastRoutineCheck = chrono::steady_clock::now(); /** Record the start time **/
    int iterations = 0;
    while(1){

        SimulateCasino(casino, flag);
        if(flag==1){
            //CloseCasino...
            //Shutdown(casino);
            break;
        }
        if (kbhit())
        {
            //clear();
            menu(casino);
        }
        auto currentTime = chrono::steady_clock::now(); /** Record current time **/
        auto elapsed = getElapsedTime(currentTime, lastRoutineCheck);
        if (elapsed.count() >= 5 || iterations == 10) {
            casino->printVectorsSize();
            //Wait(30);
            this_thread::sleep_for(chrono::milliseconds(100));
            casino->check_routine();
            lastRoutineCheck = chrono::steady_clock::now(); /** Reset the timer **/
            casino->printVectorsSize();
            //Wait(30);
            iterations=0;
        }
        if(randomNumberGeneratorInterval(0,3) == 3){
            casino->changeMachineFailProbability();
        }
        casino->RandomOddImprovement();
        this_thread::sleep_for(chrono::milliseconds(100)); /** To reduce CPU usage **/

        casino->printVectorsSize();
        ++iterations;
    }

    const size_t mem = casino->Total_Memory();
    cout << "\nMemoria total ocupado pelo casino: " << mem << "bytes" << endl;
    cout << "\nTotal Profit Casino: " << casino->getTotalProfits() << endl;
    /** Callback at program ending **/
    auto endTime = std::chrono::steady_clock::now();
    static auto time_executing = (getElapsedTime(startTime, endTime).count())/60;
    exit_message = "[Execution time]: " + to_string(time_executing);
    atexit([] { cout << "Execution time: " << time_executing << "minutes." ;});
    atexit(logAtExit);
    Shutdown(casino);
    const size_t memf = casino->Total_Memory();
    cout << "\nMemoria total ocupado pelo casino: " << memf << "bytes" << endl;
    return 0;
}

/*********************************************************************
 * @brief Function to log exit message at the end of the program.    *
 *                                                                   *
 *          It logs the exit message (static var) to the logfile\    *
 *          at the end of the program using the atexit()\            *
 *          function call back.                                      *
 *                                                                   *
 * @see atexit()                                                     *
 * @return None.                                                     *
 *********************************************************************/
void logAtExit() {
    logging(logfile, __FUNCTION__, exit_message);
}

/********************************************************************************************************************************************************************************
 * @brief Simulates the operation of a casino over multiple iterations until a specified closing time.                                                                          *
 *                                                                                                                                                                              *
 *      This standalone function orchestrates the simulation of a casino's operation. It increments a static iteration counter on each call, simulating one iteration           *
 *      of casino operation by invoking the `Run` method on the provided `Casino` object. The simulation checks the current time against a predetermined closing time           *
 *      (4 AM). If the closing time is reached, it sets a flag to signal the end of the simulation and logs the total number of iterations completed.                           *
 *                                                                                                                                                                              *
 * @param casino Pointer to a `Casino` object representing the casino to simulate.                                                                                              *
 * @param flag Reference to an `u_int8_t` variable used to signal the end of the simulation (1 indicates the casino should close).                                              *
 *                                                                                                                                                                              *
 * @see Casino::Run() for the logic executed in each iteration of the simulation.                                                                                               *
 * @see Casino::getClock() and Clock::getTime() for obtaining the current simulation time.                                                                                      *
 * @see logging() for logging the total number of iterations upon simulation completion.                                                                                        *
 *                                                                                                                                                                              *
 * @exception invalid_argument Thrown if a null `Casino` pointer is passed.                                                                                                     *
 * @exception runtime_error Thrown if an error occurs during the simulation (e.g., within the `Run` method of the `Casino`).                                                    *
 * @exceptsafe This function attempts to provide basic exception safety. It logs errors and exits the program in case of failure.                                               *
 *                                                                                                                                                                              *
 * @return void. This function does not return a value but may exit the program upon encountering a critical error.                                                             *
 ********************************************************************************************************************************************************************************/
void SimulateCasino( Casino *casino, u_int8_t &flag){
    static int iterations =0;
    try{
        ++iterations;
        if(casino == nullptr) throw invalid_argument{"Casino is null."};
        casino->Run();

        time_t timeToClose = casino->getClock()->getTime();

        if (localtime(&timeToClose)->tm_hour == 04) {
            //Function to start closing casino
            flag = 1;
            cout << "Number of iterations: " << iterations << endl;
            logging(logfile, "Total number of iterations through simulation", to_string(iterations));
        }
    }catch(invalid_argument &ex){
        cerr << "Invalid argument passed as parameter -> "<< ex.what();
        logging(error_logfile, __FUNCTION__ , ex.what());
        exit(EXIT_FAILURE);
    }catch(runtime_error &ex){
        cerr << "ERROR OCCURRED ->"<< ex.what();
        logging(error_logfile, __FUNCTION__ , ex.what());
        exit(EXIT_FAILURE);
    }
}

/********************************************************************************************************************************************************************************
 * @brief Gracefully shuts down a casino, generating a final report and releasing resources.                                                                                    *
 *                                                                                                                                                                              *
 *      This function is responsible for the orderly shutdown of a casino's operations. It first calls the `Report` method on the given `Casino` object to generate             *
 *      a final report of the casino's state. After an optional wait period, it then safely deletes the `Casino` object, freeing up any resources it was using.                 *
 *      This function ensures that all necessary cleanup and final reporting are performed before the program terminates or the casino simulation ends.                         *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object that is to be shut down.                                                                                                        *
 *                                                                                                                                                                              *
 * @see Casino::Report() for how the final state report of the casino is generated.                                                                                             *
 * @see Wait() for introducing a delay before the actual shutdown, which might be useful for concluding any pending operations or simply for effect.                            *
 *                                                                                                                                                                              *
 * @exception std::runtime_error Captures and logs any runtime errors that occur during the shutdown process, particularly during report generation.                            *
 * @exceptsafe This function provides basic exception safety by ensuring that an exception does not prevent the `Casino` object from being deleted and resources\               *
 * from being freed. However, it may terminate the program if an exception is caught.                                                                                           *
 *                                                                                                                                                                              *
 * @return void. This function does not return a value but cleans up resources associated with the `Casino` object.                                                             *
 ********************************************************************************************************************************************************************************/
void Shutdown(Casino *casino){
    try {
        casino->Report(reportfile);
        //do smth maybe...
        Wait(5);
        delete casino;
    } catch (const std::runtime_error &e) {
        std::cerr << "An error occurred: " << e.what() << '\n';
    }
}

/********************************************************************************************************************************************************************************
 * @brief Displays an interactive menu for the casino simulation and handles user input.                                                                                        *
 *                                                                                                                                                                              *
 *      This function presents a user interface for interacting with various aspects of the casino simulation. Users can view casino information, save data to a file,          *
 *      check simulated time, view rankings of machines and users, access more options through a submenu, or shut down the simulation. The function ensures input               *
 *      validation and provides feedback for invalid choices. It employs a loop to keep the menu active until the user chooses to exit or shut down the simulation.             *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object for which the menu is being displayed.                                                                                          *
 *                                                                                                                                                                              *
 * @see beautify() for enhancing menu presentation.                                                                                                                             *
 * @see Casino::Listing() for displaying casino information.                                                                                                                    *
 * @see listingToFile() for saving casino information to a file.                                                                                                                *
 * @see printTime() for displaying the current simulated time.                                                                                                                  *
 * @see ROTW(), ROTMU(), MFU(), MWU() for displaying various rankings.                                                                                                          *
 * @see submenu() for accessing additional options.                                                                                                                             *
 * @see Shutdown() for gracefully ending the simulation and cleaning up resources.                                                                                              *
 * @see logging() for logging menu interactions and choices.                                                                                                                    *
 *                                                                                                                                                                              *
 * @exception None directly thrown by this function, but exceptions may be thrown by called functions and are handled appropriately.                                            *
 * @exceptsafe The function is designed to be exception-neutral, with attempts to handle exceptions thrown by operations within the menu.                                       *
 *                                                                                                                                                                              *
 * @return void. No return value, but the function controls the flow of interaction within the simulation until exit or shutdown is selected.                                   *
 ********************************************************************************************************************************************************************************/
void menu(Casino* casino) {
    if(!casino) exit(-1);
    int choice;
    logging(logfile, __FUNCTION__, "ACCESSED");
    this_thread::sleep_for(std::chrono::seconds(5));
    do {
        beautify("<MENU>");
        cout << "###   $<1> Show Casino Information.\n"
             << "###   $<2> Save casino information to file.\n"
             << "###   $<3> Check what time it is to the simulated software.\n"
             << "###   $<4> List Ranking of the WEAK (machines).\n"
             << "###   $<5> List Ranking of the MOST used (machines).\n"
             << "###   $<6> List Ranking of most frequent users.\n"
             << "###   $<7> List Ranking of most chicken dinner users (winners).\n"
             << "###   $<8> [More options].\n"
             << "###   $<9> Shutdown current simulation.\n"
             << "###   $<0> Exit the menu and return the flow control to the simulation.\n"
             << "\n\n\t [<Enter your choice>]: ";

        if (!(cin >> choice)) {
            cin.clear(); /** Clear error state **/
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /** Discard bad input **/
            cout << "Invalid input. Please enter a number.\n";
            continue; /** Skip the rest of this iteration **/
        }
        /** Now safely ignore any extra input until the next newline **/
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "CHOICE -> " << choice << endl;
        time_t currentTime{};
        if(choice == 3)  currentTime = casino->getClock()->getTime();
        switch (choice) {
            case 1:
                cout << "You selected Option 1 - Show Casino information\n";
                casino->Listing();
                logging(logfile, __FUNCTION__, "SHOWING Casino");
                break;
            case 2:
                cout << "You selected Option 2 - Save Casino information to file\n";
                listingToFile(casino);
                logging(logfile, __FUNCTION__, "SHOWING Casino");
                break;
            case 3:
                cout << "You selected Option 3 - Check what time it is to the simulated software.\n";
                printTime(currentTime);
                break;
            case 4:
                cout << "You selected Option 4 - List Ranking of the WEAK (machines).\n";
                ROTW(casino);
                break;
            case 5:
                cout << "You selected Option 5 - List Ranking of the MOST used (machines).\n";
                ROTMU(casino);
                break;
            case 6:
                cout << "You selected Option 6 - List Ranking of most frequent users.\n";
                MFU(casino);
                break;
            case 7:
                cout << "You selected Option 7 - List Ranking of most chicken dinner users (winners).\n";
                MWU(casino);
                break;
            case 8:
                cout << "You selected Option 8 - [More Options].\n";
                submenu(casino);
                break;
            case 9:
                cout << "You selected Option 9 - Shutting down simulation...\n";
                logging(logfile, __FUNCTION__, "EXITING THE SIMULATION");
                // Additional logic for closing casino
                Shutdown(casino);
                exit(1);
            case 0:
                logging(logfile, __FUNCTION__, "EXITING THE MENU->RETURNING FLOW CONTROL TO SIMULATION");
                cout << "Exiting the menu and returning the flow control to run...\n";
                this_thread::sleep_for(chrono::seconds(2));
                break;
            default:
                logging(logfile, __FUNCTION__, "INVALID CHOICE GIVEN");
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        cout << "\n";
    } while (choice != 0);
}

/********************************************************************************************************************************************************************************
 * @brief Displays the ranking of the weakest machines in the Casino.                                                                                                           *
 *                                                                                                                                                                              *
 *      This function showcases the machines with the highest failure rates. It calls the Casino's  `Ranking_of_the_weaks` method to obtain a list of machine                   *
 *      descriptions sorted by their weakness. The function then iterates through this list, printing each entry. It beautifies the output for better readability and           *
 *      handles cases where the list might be empty, indicating no weak machines or an error.                                                                                   *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object from which the weak machines' ranking is to be retrieved.                                                                       *
 *                                                                                                                                                                              *
 * @see Casino::Ranking_of_the_weaks() for how the ranking is determined and the list of weak machines is obtained.                                                             *
 * @see beautify() for enhancing the presentation of the ranking header.                                                                                                        *
 *                                                                                                                                                                              *
 * @exception None. This function does not throw exceptions directly but checks for and handles errors in obtaining the ranking.                                                *
 * @exceptsafe This function is exception-neutral, ensuring no state changes in the `Casino` object. Memory allocated for the list is safely deleted after use.                 *
 *                                                                                                                                                                              *
 * @return void. No return value, but prints the ranking of weak machines to the standard output.                                                                               *
 ********************************************************************************************************************************************************************************/
void ROTW(Casino* casino){
    beautify(" Ranking of the ~W E A K~");
    auto sl = casino->Ranking_of_the_weaks();
    if(sl->empty()){
        cerr << "An error as occured...\n" << endl;
    }
    else{
        for(auto &entry : *sl){
            cout << entry << endl;
        }
    }
    delete sl;
}

/********************************************************************************************************************************************************************************
 * @brief Displays the ranking of the most used machines in the Casino.                                                                                                         *
 *                                                                                                                                                                              *
 *      This function showcases the machines that have been used the most based on usage metrics such as play counts. It calls the Casino's `Ranking_of_the_most_used`          *
 *      method to obtain a list of machine pointers sorted by their usage. The function then iterates through this list, printing the detailed description of each              *
 *      machine. It beautifies the output for better readability and handles cases where the list might be empty, indicating an error or no usage data.                         *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object from which the most used machines' ranking is to be retrieved.                                                                  *
 *                                                                                                                                                                              *
 * @see Casino::Ranking_of_the_most_used() for how the ranking is determined and the list of most used machines is obtained.                                                    *
 * @see beautify() for enhancing the presentation of the ranking header.                                                                                                        *
 * @see Machine::toStringOut() for obtaining the string representation of each machine in the list.                                                                             *
 *                                                                                                                                                                              *
 * @exception None. This function does not throw exceptions directly but checks for and handles errors in obtaining the ranking.                                                *
 * @exceptsafe This function is exception-neutral, ensuring no state changes in the `Casino` object. Memory allocated for the list is safely deleted after use.                 *
 *                                                                                                                                                                              *
 * @return void. No return value, but prints the ranking of the most used machines to the standard output.                                                                      *
 ********************************************************************************************************************************************************************************/
void ROTMU(Casino* casino){
    beautify(" Ranking of the ~Most USED~");
    auto ml = casino->Ranking_of_the_most_used();
    if(ml->empty()){
        cerr << "An error as occurred...\n" << endl;
    }
    else{
        for(auto &entry : *ml){
            cout << entry->toStringOut() << endl;
        }
    }
    delete ml;
}

/********************************************************************************************************************************************************************************
 * @brief Displays the ranking of the most frequent users in the Casino.                                                                                                        *
 *                                                                                                                                                                              *
 *      This function highlights the users who visit and use the casino facilities the most, based on frequency metrics such as time spent in the casino.                       *
 *      It retrieves a list of user pointers sorted by their frequency of visits from the `Casino` object's `Most_Frequent_Users` method.                                       *
 *      Each user's information is then printed to the standard output. The output is formatted for readability, and the function handles cases where the list might be empty,  *
 *      indicating either an error or the absence of user data.                                                                                                                 *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object from which the most frequent users' ranking is to be retrieved.                                                                 *
 *                                                                                                                                                                              *
 * @see Casino::Most_Frequent_Users() for the method that determines the ranking and obtains the list of frequent users.                                                        *
 * @see beautify() for enhancing the presentation of the ranking header.                                                                                                        *
 * @see User::toString() for obtaining the string representation of each user in the list.                                                                                      *
 *                                                                                                                                                                              *
 * @exception None. This function does not throw exceptions directly but checks for and handles errors in obtaining the ranking.                                                *
 * @exceptsafe This function is exception-neutral, ensuring no state changes in the `Casino` object. Memory allocated for the list is safely deleted after use.                 *
 *                                                                                                                                                                              *
 * @return void. No return value, but prints the ranking of the most frequent users to the standard output.                                                                     *
 ********************************************************************************************************************************************************************************/
void MFU(Casino* casino){
    beautify(" Ranking of the ~Most Frequent Users~");
    auto mfu = casino->Most_Frequent_Users();
    if(mfu->empty()){
        cerr << "An error as occurred...\n" << endl;
    }
    else{
        for(auto &entry : *mfu){
            cout << entry->toString() << endl;
        }
    }
    delete mfu;
}

/********************************************************************************************************************************************************************************
 * @brief Displays the ranking of users with the most wins in the Casino.                                                                                                       *
 *                                                                                                                                                                              *
 *      This function presents the users who have won the most in terms of earnings within the casino. It leverages the `Casino` object's `Most_Wins_Users` method to obtain    *
 *      a sorted list of user pointers based on their winnings. The function iterates through this list, printing detailed information about each user.                         *
 *      It employs a beautification process to enhance the readability of the ranking's header and handles scenarios where the list might be empty.                             *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object from which the ranking of users with the most wins is retrieved.                                                                *
 *                                                                                                                                                                              *
 * @see Casino::Most_Wins_Users() for the method that calculates the ranking and retrieves the list of winning users.                                                           *
 * @see beautify() for formatting the presentation of the ranking header.                                                                                                       *
 * @see User::toString() for generating the string representation of each user in the ranking.                                                                                  *
 *                                                                                                                                                                              *
 * @exception None. While this function does not directly throw exceptions, it includes error handling for cases where the ranking list is empty.                               *
 * @exceptsafe This function is exception-neutral, ensuring no state changes in the `Casino` object. Memory allocated for the list is properly freed after use.                 *
 *                                                                                                                                                                              *
 * @return void. This function does not return a value but outputs the ranking of users with the most wins to the standard console.                                             *
 ********************************************************************************************************************************************************************************/
void MWU(Casino* casino){
    beautify(" Ranking of the ~Most Winners Users~");
    auto mwu = casino->Most_Wins_Users();
    if(mwu->empty()){
        cerr << "An error as occurred...\n" << endl;
    }
    else{
        for(auto &entry : *mwu){
            cout << entry->toString() << endl;
        }
    }
    delete mwu;
}

/********************************************************************************************************************************************************************************
 * @brief Displays an interactive submenu for additional operations within the Casino simulation.                                                                               *
 *                                                                                                                                                                              *
 *      This function presents a secondary user interface for interacting with more specific aspects of the casino simulation, such as listing machine UIDs, turning            *
 *      off machines by UID, getting the state of a machine by UID, listing machines by type, and listing machines with a winning percentage higher than a certain              *
 *      threshold. It validates user input and provides feedback for invalid choices, utilizing a loop to keep the submenu active until the user chooses to exit.               *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object for which the submenu is being displayed.                                                                                       *
 *                                                                                                                                                                              *
 * @see beautify() for enhancing submenu presentation.                                                                                                                          *
 * @see Casino::ListMachinesUID() for listing all machine UIDs.                                                                                                                 *
 * @see Casino::TurnOff() for turning off a specific machine by UID.                                                                                                            *
 * @see Casino::getState() for getting the state of a specific machine by UID.                                                                                                  *
 * @see Casino::Listing() for listing machines with a winning percentage higher than a specified threshold.                                                                     *
 * @see subsubmenu() for navigating to further nested menus.                                                                                                                    *
 * @see logging() for logging submenu interactions and choices.                                                                                                                 *
 *                                                                                                                                                                              *
 * @exception None directly thrown by this function, but exceptions may be thrown by called functions and are handled appropriately.                                            *
 * @exceptsafe The function is designed to be exception-neutral, with attempts to handle exceptions thrown by operations within the submenu.                                    *
 *                                                                                                                                                                              *
 * @return void. No return value, but the function controls the flow of interaction within the submenu until exit is selected.                                                  *
 ********************************************************************************************************************************************************************************/
void submenu(Casino* casino) {
    if (!casino) exit(-1);
    int choice;
    logging(logfile, __FUNCTION__, "ACCESSED");
    this_thread::sleep_for(std::chrono::seconds(5));
    do {
        beautify("<SUBMENU>");
        cout << "###   $<1> List Machines UIDs.\n"
             << "###   $<2> Turn Off Machine by UID.\n"
             << "###   $<3> Get Machine State by UID.\n"
             << "###   $<5> List Machines by type.\n"
             << "###   $<7> List Machines with winning percentage higher than 50%.\n"\
             << "###   $<0> Exit the submenu.\n"
             << "\n\n\t [<Enter your choice>]: ";

        if (!(cin >> choice)) {
            cin.clear(); /** Clear error state **/
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /** Discard bad input **/
            cout << "Invalid input. Please enter a number.\n";
            continue; /** Skip the rest of this iteration **/
        }
        /** Now safely ignore any extra input until the next newline **/
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "CHOICE -> " << choice << endl;
        int id;
        switch (choice) {
            case 1:
                cout << "You selected Option 1 - List Machines UIDs.\n";
                casino->ListMachinesUID();
                logging(logfile, __FUNCTION__, "List Machines UIDs");
                break;
            case 2:
                cout << "You selected Option 2 - Turn Off Machine by UID.\n";
                cout << "Machine UID to turn off: ";
                this_thread::sleep_for(std::chrono::seconds(1));
                int machineUID;
                if (!(cin >> machineUID)) {
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
                    cout << "Invalid input. Please enter a valid UID.\n";
                    break;
                }
                cout << "CHOICE -> " << machineUID << endl;
                cout << "FROM:  " << machineSTATEToString(casino->getState(machineUID)) << endl;

                casino->TurnOff(machineUID);
                cout << "TO:  " << machineSTATEToString(casino->getState(machineUID)) << endl;
                logging(logfile, __FUNCTION__, "Turn Off Machine by UID");
                break;
            case 3:
                cout << "You selected Option 3 - Get Machine State by UID.\n";
                cout << "Machine UID to get state: ";
                int UID;
                if (!(cin >> UID)) {
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
                    cout << "Invalid input. Please enter a valid UID.\n";
                    break;
                }
                cout << "CHOICE -> " << UID << endl;
                cout << machineSTATEToString(casino->getState(UID)) << endl;
                logging(logfile, __FUNCTION__, "Get Machine State by UID");
                break;
            case 5:
                cout << "You selected Option 5 - List Machine by type.\n";
                subsubmenu(casino);
                break;
            case 7:
                cout << "You selected Option 7 - List Machines with winning percentage higher than 50%.\n";
                casino->Listing(0.5f);
                logging(logfile, __FUNCTION__, "List Machines with winning percentage higher than 50%.");
                break;
            case 0:
                logging(logfile, __FUNCTION__, "EXITING THE SUBMENU->RETURNING TO MENU");
                cout << "Exiting the submenu and returning to teh submenu...\n";
                this_thread::sleep_for(chrono::seconds(10));
            default:
                logging(logfile, __FUNCTION__, "INVALID CHOICE GIVEN");
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        cout << "\n";
    } while (choice != 0);
}

/********************************************************************************************************************************************************************************
 * @brief Displays an interactive subsubmenu for operations related to machine types within the Casino simulation.                                                              *
 *                                                                                                                                                                              *
 *      This function extends the user interface to allow for interactions specifically focused on the different types of machines available in the casino. Users can           *
 *      choose to list machines based on their type, such as CLASSIC_SLOT, BLACKJACK, ROULETTE, or CRAPS (the ones that are implemented).                                       *
 *      The function validates user input and loops to keep the subsubmenu active until the user decides to exit back to the previous menu level.                               *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object for which the subsubmenu is being displayed.                                                                                    *
 *                                                                                                                                                                              *
 * @see beautify() for enhancing subsubmenu presentation.                                                                                                                       *
 * @see Casino::List_Types() for listing machines of a specific type.                                                                                                           *
 * @see logging() for logging subsubmenu interactions and choices.                                                                                                              *
 *                                                                                                                                                                              *
 * @exception None directly thrown by this function, but exceptions may be thrown by called functions and are handled appropriately.                                            *
 * @exceptsafe The function is designed to be exception-neutral, with attempts to handle exceptions thrown by operations within the subsubmenu.                                 *
 *                                                                                                                                                                              *
 * @return void. No return value, but the function controls the flow of interaction within the subsubmenu until exit is selected.                                               *
 ********************************************************************************************************************************************************************************/
void subsubmenu(Casino* casino) {
    if (!casino) exit(-1);
    int choice;
    logging(logfile, __FUNCTION__, "ACCESSED");
    this_thread::sleep_for(std::chrono::seconds(5));
    do {
        beautify("<SUBSUBMENU>");
        cout << "###   $<-> Select Machine type.\n"
             << "###   $<1> CLASSIC_SLOT.\n"
             << "###   $<4> BLACKJACK.\n"
             << "###   $<5> ROULETTE.\n"
             << "###   $<6> CRAPS.\n"\
             << "###   $<0> Exit the submenu.\n"
             << "\n\n\t [<Enter your choice>]: ";

        if (!(cin >> choice)) {
            cin.clear(); /** Clear error state **/
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /** Discard bad input **/
            cout << "Invalid input. Please enter a number.\n";
            continue; /** Skip the rest of this iteration **/
        }
        /** Now safely ignore any extra input until the next newline **/
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "CHOICE -> " << choice << endl;
        switch (choice) {
            case 1:
                casino->List_Types(MACHINE_TYPE::CLASSIC_SLOT);
                break;
            case 4:
                casino->List_Types(MACHINE_TYPE::BLACKJACK);
                break;
            case 5:
                casino->List_Types(MACHINE_TYPE::ROULETTE);
                break;
            case 6:
                casino->List_Types(MACHINE_TYPE::CRAPS);
                break;
            case 0:
                logging(logfile, __FUNCTION__, "EXITING THE SUBSUBMENU->RETURNING TO SUBMENU");
                cout << "Exiting the submenu and returning to teh submenu...\n";
                this_thread::sleep_for(chrono::seconds(10));
            default:
                logging(logfile, __FUNCTION__, "INVALID CHOICE GIVEN");
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        cout << "\n";
    }while (choice != 0);
}

/********************************************************************************************************************************************************************************
 * @brief Exports the listing of the Casino's current state to a file.                                                                                                          *
 *                                                                                                                                                                              *
 *      This function is responsible for writing the current state and information of the casino, including details about machines, users, and other relevant data,             *
 *      to a specified file. It opens the file in append mode, ensuring that existing content is not overwritten. If the file cannot be opened, or if any other error           *
 *      occurs during the operation, an exception is caught and handled by reporting the error to the standard error stream.                                                    *
 *                                                                                                                                                                              *
 * @param casino Pointer to the `Casino` object whose information is to be exported.                                                                                            *
 *                                                                                                                                                                              *
 * @see Casino::Listing(std::ostream&) for the method that generates the listing of the casino's current state.                                                                 *
 *                                                                                                                                                                              *
 * @exception std::ios_base::failure Thrown if the file specified by `casinoFile` cannot be opened for writing.                                                                 *
 * @exception std::runtime_error Potentially thrown by the `Listing` method of the `Casino` class, indicating an error in generating the listing.                               *
 * @exceptsafe This function is exception-safe in that it catches and handles all exceptions locally, ensuring that the program remains stable even in the face of errors.      *
 *                                                                                                                                                                              *
 * @return void. No return value, but the function may generate output in a file or produce error messages on failure.                                                          *
 ********************************************************************************************************************************************************************************/
void listingToFile(Casino* casino){
    try {
        std::ofstream file{casinoFile, std::ios::app};
        if (!file.is_open())
            throw std::ios_base::failure("Unable to open file: " + casinoFile);
        casino->Listing(file);
    } catch (const std::ios_base::failure &e) {
        std::cerr << "An error occurred while opening the file -> " << e.what() << '\n';
    }catch (const std::runtime_error &e) {
        std::cerr << "An error occurred -> " << e.what() << '\n';
    }
}
