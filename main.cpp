#include <iostream>

#include "Library/Headers/Casino.h"
#include "Library/Headers/kbhitmodule.h"

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

    //Test Data
    //initialize rand
    srand(time(nullptr));
    /*


    User *utilizador = new User("123456789", "Joao", "Porto", 20);

    utilizador->setMoney(5000);

   /*
    Roulette *roleta = new Roulette(1, 2);
    roleta->Play(utilizador);


    ClassicSlot *slot = new ClassicSlot(1, 2);
    slot->Play(utilizador);

     */
    User *usr = new User("123456789", "Joao", "Porto", 20);
    Machine *testMachine = new Roulette();
    // Use dynamic_cast to call printMap on a Machine pointer that points to a Roulette object
    auto* roulettePtr = dynamic_cast<Roulette*>(testMachine);
    if (roulettePtr) {
        roulettePtr->printMap();
    } else {
        std::cerr << "Incorrect cast from Machine* to Roulette*" << std::endl;
    }

    usr->setMoney(1000000);
    std::cout << __FUNCTION__  << std::endl;
    std::cout << "USER MONEY TO BET: -->" << usr->getMoney() << std::endl;
    /**
     * KEYBOARD TEST RUN *
     */

    while(1) {
        roulettePtr->Play(usr);
        if (kbhit())
        {
          std::cout << "HELLO KEYBOARD" << std::endl; sleep(30);
        }
    }




    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
