#include <iostream>

#include "Library/Headers/Casino.h"
#include "Library/Headers/kbhitmodule.h"


#if defined(_WIN32) || defined(_WIN64)
void clear(){system("cls");}
#else
void clear(){system("clear");}
#endif

void SimulateCasino( Casino *casino, u_int8_t &flag);
void menu(Casino* casino);
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

    Casino *casino = new Casino("Casino_name");
    if( casino->Load("../Files/I/CasinoInfo.xml") ) beautify(" Loaded successful ") ;
    casino->ReadPeopleFile();
    casino->Listing();

    User *utilizador = new User("123456789", "Joao", "Porto", 20);
    utilizador->setMoney(5000);

    Clock *ptrClock = casino->getClock();
    ptrClock->StartClock(500, "10:00:00");
    u_int8_t flag = 0;
    while(1){

        SimulateCasino(casino, flag);
        if(flag==1){
            break;
        }
        if (kbhit())
        {
            //clear();
            menu(casino);
            //  char option = getchar();
            // ENTER TO THE MENU FUCNTION...
        }

    }

    //Wait(1000);
    //casino->Run();

    const size_t mem = casino->Total_Memory();
    cout << "\nMemoria total ocupado pelo casino: " << mem << "bytes" << endl;
    std::atexit([] {std::cout << "***std::atexit callback executing***\n";});


    //return 0;
}


void SimulateCasino( Casino *casino, u_int8_t &flag){
    time_t time_passed = casino->getClock()->getTime();


    casino->Run();


    time_t timeToClose = casino->getClock()->getTime();
    if (localtime(&timeToClose)->tm_hour == 04){
        //Function to start closing casino
        flag = 1;
    }
}


void menu(Casino* casino) {
    int choice;
    logging(logfile, __FUNCTION__, "ACCESSED");
    std::this_thread::sleep_for(std::chrono::seconds(10));
    do {
        beautify("<MENU>");
        std::cout << "###   $<1> Show Casino Information.\n"
                  << "###   $<2> [TBD]\n"
                  << "###   $<3> [TBD]\n"
                  << "###   $<4> Check what time it is to the simulated software.\n"
                  << "###   $<5> [TBD].\n"
                  << "###   $<9> Shutdown current simulation.\n"
                  << "###   $<0> Exit the menu and return the flow control to the simulation.\n"
                  << "\n\n\t <Enter your choice>: ";

        std::cin >> choice;

        // Clearing input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "CHOICE -> " << choice << std::endl;
        time_t currentTime{};
        if(choice == 4)  currentTime = casino->getClock()->getTime();
        switch (choice) {
            case 1:
                std::cout << "You selected Option 1 - Show Casino information\n";
                logging(logfile, __FUNCTION__, "SHOWING Casino");
                // Additional logic for option 1
                break;
            case 2:
                // Logic for option 2
                break;
            case 3:
                // Logic for option 3
                break;
            case 4:
                std::cout << "You selected Option 4\n";
                printTime(currentTime);
                break;
            case 5:
                // Logic for option 5
                break;
            case 9:
                logging(logfile, __FUNCTION__, "EXITING THE SIMULATION");
                // Additional logic for option 9
                delete casino;
                exit(1);
            case 0:
                logging(logfile, __FUNCTION__, "EXITING THE MENU->RETURNING FLOW CONTROL TO SIMULATION");
                std::cout << "Exiting the menu and returning the flow control to run...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            default:
                logging(logfile, __FUNCTION__, "INVALID CHOICE GIVEN");
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        std::cout << "\n";
    } while (choice != 0);
}