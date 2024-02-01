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

/*******************************************************************************************************************************************************************
 * @brief Function to simulate the casino.                                                                                                                         *
 *                                                                                                                                                                 *
 *          Function that simulates the casino "behaviour" by grouping together the a few important functions to simulate the casino behaviour.                    *
 *          It has a static integer variable that gets incremented every time the function gets called (For statistics purposes).                                  *
 *          It checks whether the time the casino closes has come, and if the answer is yes, it changes the received flag to 1 to signal the main program to stop. *
 *                                                                                                                                                                 *
 * @see Casino::Run                                                                                                                                                *
 * @see Casino::getClock()                                                                                                                                         *
 * @see Clock::getTime()                                                                                                                                           *
 * @see logging()                                                                                                                                                  *
 * @throw std::invalid_argument If casino is a null pointer                                                                                                        *
 * @exceptsafe basic -> It throws an invalid_argument exception in case of null-pointer, other than that it catches runtime_errors.                                *
 * @param casino pointer to a casino object                                                                                                                        *
 * @param flag received as a reference, to keep track of whether the casino needs to close or not.                                                                 *
 * @return None.                                                                                                                                                   *
 *******************************************************************************************************************************************************************/
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

/*****************************************************************************************************************************************************************************
 * @brief Function to shutdown/close the casino.                                                                                                                             *
 *                                                                                                                                                                           *
 *          Function that simulates the casino closing "behaviour" by writing the casino current state (at function call time) to a XML file amd calls casino deconstructor. *
 *                                                                                                                                                                           *
 * @see Casino::~Casino()                                                                                                                                                    *
 * @see Casino::Report()                                                                                                                                                     *
 * @see Wait()                                                                                                                                                               *
 * @throw std::runtime_error If something goes wrong during execution                                                                                                        *
 * @exceptsafe basic - It throws a runtime_error in case of null-pointer, other than that is unpredictable behaviour                                                         *
 * @param casino pointer to a casino object                                                                                                                                  *
 * @return None.                                                                                                                                                             *
 *****************************************************************************************************************************************************************************/
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

/*******************************************************************************************************************************
 * @brief Menu for when the simulation is running and the user pressed a keyboard key.                                         *
 *                                                                                                                             *
 *          Can Show the casino current state;                                                                                 *
 *          Save the casino current state to a file;                                                                           *
 *          Check what time it is to the simulated casino object;                                                              *
 *          Performs various Listings (ranking of the weak, most used machines, most frequent users, users who win the most);  *
 *          Shutdown current simulation and exit the program;                                                                  *
 *          Exit the menu and return the flow control to the function that called this one.                                    *
 *                                                                                                                             *
 * @see logging()                                                                                                              *
 * @see beautify()                                                                                                             *
 * @see Casino::Listing()                                                                                                      *
 * @see Clock::ListingToFile()                                                                                                 *
 * @see printTime()                                                                                                            *
 * @see ROTW()                                                                                                                 *
 * @see ROTMU()                                                                                                                *
 * @see MFU()                                                                                                                  *
 * @see MWU()                                                                                                                  *
 * @see submenu()                                                                                                              *
 * @see Shutdown()                                                                                                             *
 * @exceptsafe none - Shall not throw exceptions                                                                               *
 * @param casino pointer to a casino object                                                                                    *
 * @param choice[in] user choice of the options                                                                                *
 * @return None.                                                                                                               *
 *******************************************************************************************************************************/
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

/************************************************************************
 * @brief Listing to the output the Ranking of the Weak machines.       *
 *                                                                      *
 * @see beautify()                                                      *
 * @see Casino::Ranking_of_the_weaks()                                  *
 * @exceptsafe none - Shall not throw exceptions                        *
 * @param casino pointer to a casino object                             *
 * @return None.                                                        *
 ************************************************************************/
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

/*****************************************************************************
 * @brief Listing to the output the Ranking of the most used machines.       *
 *                                                                           *
 * @see beautify()                                                           *
 * @see Casino::Ranking_of_the_most_used()                                   *
 * @see Machine::toStringOut()                                               *
 * @exceptsafe none - Shall not throw exceptions                             *
 * @param casino pointer to a casino object                                  *
 * @return None.                                                             *
 *****************************************************************************/
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

/*****************************************************************************
 * @brief Listing to the output the Ranking of the most frequent users       *
 *                                                                           *
 * @see beautify()                                                           *
 * @see Casino::Most_Frequent_Users()                                        *
 * @see User::toString()                                                     *
 * @exceptsafe none - Shall not throw exceptions                             *
 * @param casino pointer to a casino object                                  *
 * @return None.                                                             *
 *****************************************************************************/
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

/*****************************************************************************
 * @brief Listing to the output the Ranking of the most users with most wins *
 *                                                                           *
 * @see beautify()                                                           *
 * @see Casino::Most_Wins_Users()                                            *
 * @see User::toString()                                                     *
 * @exceptsafe none - Shall not throw exceptions                             *
 * @param casino pointer to a casino object                                  *
 * @return None.                                                             *
 *****************************************************************************/
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

/*********************************************************************
 * @brief Submenu of the Menu                                        *
 *                                                                   *
 *          Can List Machines Unique Identifier (UID);               *
 *          Turn Off Machine by UID;                                 *
 *          Get Machine State by UID;                                *
 *          List Machines by type; (calls subsubmenu)                *
 *          List Machines with winning percentage higher than 50%;   *
 *          Exit the submenu.                                        *
 *                                                                   *
 * @see logging()                                                    *
 * @see beautify()                                                   *
 * @see Casino::ListMachinesUID()                                    *
 * @see Casino::TurnOff()                                            *
 * @see Casino::getState()                                           *
 * @see Casino::Listing()                                            *
 * @see subsubmenu()                                                 *
 * @exceptsafe none - Shall not throw exceptions                     *
 * @param casino pointer to the casino object                        *
 * @param choice[in] user choice of the options                      *
 * @return None.                                                     *
 *********************************************************************/
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

/*************************************************************************************
 * @brief Subsubmenu of the Menu - submenu of submenu option                         *
 *                                                                                   *
 *          Can list any of the programmed machine types that belong to the casino   *
 *                                                                                   *
 * @see logging()                                                                    *
 * @see beautify()                                                                   *
 * @see Casino::List_Types()                                                         *
 * @exceptsafe none - Shall not throw exceptions                                     *
 * @param casino pointer to the casino object                                        *
 * @param choice[in] user choice of the options                                      *
 * @return None.                                                                     *
 *************************************************************************************/
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

        cin >> choice;

        /** Clearing input buffer **/
        cin.clear();
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

/*********************************************************************************************************************
 * @brief Writes the current state of the casino to a file                                                           *
 *                                                                                                                   *
 * @see logging()                                                                                                    *
 * @see beautify()                                                                                                   *
 * @see Casino::Listing()                                                                                            *
 * @throw std::ios_base::failure if an error occurs while opening the file                                           *
 * @exceptsafe basic - captures errors related to the opening of the file, and some runtime error that might occur   *
 * @param casino pointer to the casino object                                                                        *
 * @param choice[in] user choice input                                                                               *
 * @return None.                                                                                                     *
 *********************************************************************************************************************/
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
