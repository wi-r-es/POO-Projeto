#include <iostream>

#include "Library/Headers/Casino.h"
#include "Library/Headers/kbhitmodule.h"
#include "Library/Headers/utils.h"

#if defined(_WIN32) || defined(_WIN64)
void clear(){system("cls");}
string casinoFile { "Files\\O\\casinoState.txt" } ;
#else
void clear(){system("clear");}
#endif
void logAtExit();
static string exit_message;
string casinoFile { "Files/O/casinoState.txt" } ;

void SimulateCasino( Casino *casino, u_int8_t &flag);
void menu(Casino* casino);
void submenu(Casino* casino);
void listingToFile(Casino* casino);
// Example for documenting the functions from previous project
/*********************************************************************************************************************************************************************
 * @brief Loads Clients, employees, products and boxes from files. Generates hashing for clients based on the input.                                                 *
 *                                                                                                                                                                   *
 *      Receives a pointer to clients, employees, products and boxes lists and a char pointer to dynamically create a hashtable from the clients unique initials,\   *
 *      Loads the clients list from a file, aswell as the employees and products.\                                                                                   *
 *      Generates a random number of boxes.                                                                                                                          *
 *                                                                                                                                                                   *
 * @see logging()   // funcoes que sao chamadas pela funcao a documentar                                                                                                                                                 *
 * @see Load_Client()                                                                                                                                                *
 * @see Load_Funcionario()                                                                                                                                           *
 * @see Load_Produtos()                                                                                                                                              *
 * @see GenerateBoxes()                                                                                                                                              *
 * @param C : ListaGenerica* for clients/Clientes.                                                                                                                   *
 * @param F : ListaGenerica* for employees/Funcionarios.                                                                                                             *
 * @param P : ListaGenerica* for products/Produtos.                                                                                                                  *
 * @param CX : ListaGenerica* for boxes/Caixas.                                                                                                                      *
 * @param l : char* to get the number of different initials accross the clients list so it can create dynamically , a hashtable after.                               *
 * @return None.
 *
 *********************************************************************************************************************************************************************/
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
    while(1){

        SimulateCasino(casino, flag);
        if(flag==1){
            //CloseCasino...
            break;
        }
        if (kbhit())
        {
            //clear();
            menu(casino);
        }
        auto currentTime = chrono::steady_clock::now(); /** Record current time **/
        auto elapsed = getElapsedTime(currentTime, lastRoutineCheck);
        if (elapsed.count() >= 5) {
            casino->printVectorsSize();
            //Wait(30);
            this_thread::sleep_for(chrono::milliseconds(100));
            casino->check_routine();
            lastRoutineCheck = chrono::steady_clock::now(); /** Reset the timer **/
            casino->printVectorsSize();
            //Wait(30);
        }
        if(randomNumberGeneratorInterval(1,3) == 3){
            casino->changeMachineFailProbability();
        }
        casino->RandomOddImprovement();
        this_thread::sleep_for(chrono::milliseconds(100)); /** To reduce CPU usage **/

        casino->printVectorsSize();
    }

    const size_t mem = casino->Total_Memory();
    cout << "\nMemoria total ocupado pelo casino: " << mem << "bytes" << endl;

    /** Callback at program ending **/
    auto endTime = std::chrono::steady_clock::now();
    static auto time_executing = (getElapsedTime(startTime, endTime).count())/60;
    exit_message = "[Execution time]: " + to_string(time_executing);
    atexit([] { cout << "Execution time: " << time_executing << "minutes." ;});
    atexit(logAtExit);
    delete casino;
    const size_t memf = casino->Total_Memory();
    cout << "\nMemoria total ocupado pelo casino: " << memf << "bytes" << endl;
    return 0;
}
void logAtExit() {
    logging(logfile, __FUNCTION__, exit_message);
}

void SimulateCasino( Casino *casino, u_int8_t &flag){
    static int iterations =0;
    try{
        ++iterations;
        if(casino == nullptr) throw runtime_error{"Casino is null."};
        casino->Run();

        time_t timeToClose = casino->getClock()->getTime();

        if (localtime(&timeToClose)->tm_hour == 04) {
            //Function to start closing casino
            flag = 1;
            cout << "Number of iterations: " << iterations << endl;
            logging(logfile, "Total number of iterations through simulation", to_string(iterations));
        }
    }catch(runtime_error &ex){
        cerr << "ERROR OCCURRED ->"<< ex.what();
        logging(error_logfile, __FUNCTION__ , ex.what());
        exit(EXIT_FAILURE);
    }

}


void menu(Casino* casino) {
    if(!casino) exit(-1);
    int choice;
    logging(logfile, __FUNCTION__, "ACCESSED");
    this_thread::sleep_for(std::chrono::seconds(10));
    do {
        beautify("<MENU>");
        cout << "###   $<1> Show Casino Information.\n"
             << "###   $<2> Save casino information to file.\n"
             << "###   $<3> Check what time it is to the simulated software.\n"
             << "###   $<4> List Ranking of the WEAK (machines).\n"
             << "###   $<5> List Ranking of the MOST used (machines).\n"
             << "###   $<6> List Ranking of most frequent users.\n"
             << "###   $<7> List Ranking of most chicken dinner users (winners).\n"
             << "###   $<8> [Interact with machines].\n"
             << "###   $<9> Shutdown current simulation.\n"
             << "###   $<0> Exit the menu and return the flow control to the simulation.\n"
             << "\n\n\t [<Enter your choice>]: ";

        cin >> choice;

        /** Clearing input buffer **/
        cin.clear();
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

                break;
            case 5:
                cout << "You selected Option 5 - List Ranking of the MOST used (machines).\n";

                break;
            case 6:
                cout << "You selected Option 6 - List Ranking of most frequent users.\n";

                break;
            case 7:
                cout << "You selected Option 7 - List Ranking of most chicken dinner users (winners).\n";

                break;
            case 8:
                cout << "You selected Option 8 - [Interact with machines].\n";
                submenu(casino);
                break;
            case 9:
                cout << "You selected Option 9 - Shutting down simulation...\n";
                logging(logfile, __FUNCTION__, "EXITING THE SIMULATION");
                // Additional logic for closing casino
                delete casino;
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
void submenu(Casino* casino) {
    if (!casino) exit(-1);
    int choice;
    logging(logfile, __FUNCTION__, "ACCESSED");
    this_thread::sleep_for(std::chrono::seconds(10));
    do {
        beautify("<MENU>");
        cout << "###   $<1> List Machines UIDs.\n"
             << "###   $<2> Turn Off Machine by UID.\n"
             << "###   $<3> Turn Off Machine by UID.\n"
             << "###   $<7> List Machines with winning percentage higher than 50%.\n"\
             << "###   $<0> Exit the submenu.\n"
             << "\n\n\t [<Enter your choice>]: ";

        cin >> choice;

        /** Clearing input buffer **/
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "CHOICE -> " << choice << endl;
        switch (choice) {
            case 1:
                cout << "You selected Option 1 - List Machines UIDs.\n";

                logging(logfile, __FUNCTION__, "List Machines UIDs");
                break;
            case 2:
                cout << "You selected Option 2 - Turn Off Machine by UID.\n";

                logging(logfile, __FUNCTION__, "List Machines UIDs");
                break;
            case 3:
                cout << "You selected Option 3 - Turn Off Machine by UID.\n";

                logging(logfile, __FUNCTION__, "List Machines UIDs");
                break;
            case 7:
                cout << "You selected Option 7 - List Machines with winning percentage higher than 50%.\n";
                casino->Listing(0.5f);
                logging(logfile, __FUNCTION__, "List Machines UIDs");
                break;
            case 0:
                logging(logfile, __FUNCTION__, "EXITING THE SUBMENU->RETURNING TO MENU");
                cout << "Exiting the submenu and returning to teh submenu...\n";
                this_thread::sleep_for(chrono::seconds(2));
            default:
                logging(logfile, __FUNCTION__, "INVALID CHOICE GIVEN");
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        cout << "\n";
    } while (choice != 0);
}

void listingToFile(Casino* casino){
    try {
        std::ofstream file{casinoFile, std::ios::app};
        if (!file.is_open())
            throw std::runtime_error("Unable to open file: " + casinoFile);
        casino->Listing(file);
    } catch (const std::runtime_error &e) {
        std::cerr << "An error occurred: " << e.what() << '\n';
    }
}
