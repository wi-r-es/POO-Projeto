#include <iostream>
#include "Library/Headers/User.h"
#include "Library/Headers/Roulette.h"


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

    User *utilizador = new User("123456789", "Joao", "Porto", 20);

    std::cout << utilizador->getId() << std::endl;

    Roulette *roleta = new Roulette(1, 2);
    roleta->Play(utilizador);




    std::cout << "Hello, World!" << std::endl;
    return 0;
}
