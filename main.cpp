#include <iostream>

#include "Library/Headers/Casino.h"
#include "Library/Headers/kbhitmodule.h"


#if defined(_WIN32) || defined(_WIN64)
void clear(){system("cls");}
#else
void clear(){system("clear");}
#endif
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
    Wait(1000);
    casino->Run();

/*
    Machine *SlotMachine = new ClassicSlot();

    auto *slotPtr = dynamic_cast<ClassicSlot*>(SlotMachine);
    while(1) {
        slotPtr->Play(utilizador);
        if (kbhit())
        {
            clear();

          std::cout << "HELLO KEYBOARD" << std::endl; sleep(30);
        }


        cout << "DEBT OWNED -> " << utilizador->getDebt() << endl;
    }

*/
    const size_t mem = casino->Total_Memory();
    cout << "\nMemoria total ocupado pelo casino: " << mem << "bytes" << endl;
    std::atexit([] {std::cout << "***std::atexit callback executing***\n";});


    //return 0;
}