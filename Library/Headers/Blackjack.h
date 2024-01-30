//
// Created by nameless on 06/11/23.
//

/******************************************************************************************
 *  @file Blackjack.h                                                                     *
 *  @brief Class prototypes for Blackjack Machine ADT Structure/Class                     *
 *                                                                                        *
 *  This contains the prototypes for the managing of Blackjack Machines and its fields.   *
 *                                                                                        *
 ******************************************************************************************/

#ifndef CODE_BLACKJACK_H
#define CODE_BLACKJACK_H
#include "Machine.h"
/***********************************************************************************************
 * Blackjack ADT class description derived from Machine                                        *
 *                                                                                             *
 * Inherits from Machine class. Represents a specific type of machine, namely a Blackjack      *
 * game machine. In addition to the attributes inherited from Machine, it includes specific    *
 * attributes and mechanisms for playing the game of Blackjack.                                *
 *                                                                                             *
 * Values_Cards            -> Map associating card characters with their corresponding         *
 *                            integer values in the game of Blackjack.                         *
 *                            For example, 'A' might map to 1 or 11, '2' to 2, ..., 'K' to 10. *
 * Dealers_Hand            -> Vector storing the integer values of the cards currently in the  *
 *                            dealer's hand. Each integer represents a card.                   *
 * Players_Hand            -> Vector storing the integer values of the cards currently in the  *
 *                            player's hand. Similar to Dealers_Hand, each integer             *
 *                            represents a card.                                               *
 ***********************************************************************************************/
class Blackjack : public Machine {
private:
    std::map<char,int> Values_Cards;
    std::vector<int> Dealers_Hand;
    std::vector<int> Players_Hand;
public:
    /***********************************************************************************************************************************************************************
     * @brief Constructor for the Blackjack class, derived from Machine.                                                                                                   *
     *                                                                                                                                                                     *
     * This constructor initializes an instance of the `Blackjack` class, a specific type of gaming machine. It sets the machine's type to `BLACKJACK` and                 *
     * initializes its position to the provided coordinates (`posX`, `posY`). Additionally, it initializes the `Values_Cards` map with the values of the cards             *
     * used in a game of blackjack.                                                                                                                                        *
     *                                                                                                                                                                     *
     * The card values are set as follows:                                                                                                                                 *
     *      - 'A' (Ace) is valued at 1.                                                                                                                                    *
     *      - Number cards '2' to '9' are valued at their face values.                                                                                                     *
     *      - 'J' (Jack), 'Q' (Queen), and 'K' (King) are each valued at 10.                                                                                               *
     *                                                                                                                                                                     *
     * This initialization is essential for the blackjack game logic, as it determines the scoring system for the game.                                                    *
     *                                                                                                                                                                     *
     * @note This constructor specifically sets up the blackjack card values and inherits position initialization from the `Machine` base class.                           *
     *                                                                                                                                                                     *
     * @see Machine class for the base class constructor and initializations.                                                                                              *
     * @see Values_Cards for the map holding card values.                                                                                                                  *
     *                                                                                                                                                                     *
     * @param posX The x-coordinate of the machine's position.                                                                                                             *
     * @param posY The y-coordinate of the machine's position.                                                                                                             *
     *                                                                                                                                                                     *
     * @exception None. This constructor does not explicitly throw any exceptions. However, exceptions may be thrown by base class initializers or std::map operations.    *
     * @exceptsafe This constructor is exception-neutral. It offers no guarantees if an exception is thrown during initialization.                                         *
     *                                                                                                                                                                     *
     * @return None. Constructors do not return values.                                                                                                                    *
     ***********************************************************************************************************************************************************************/
    Blackjack(int posX, int posY);

    /***********************************************************************************************************************************************************************
     * @brief Default Constructor for Blackjack.                                                                                                                           *
     *                                                                                                                                                                     *
     * This default constructor initializes an instance of the `Blackjack` class, a specific type of gaming machine. It sets the machine's type to `BLACKJACK` and         *
     * initializes its position to default values (0, 0). Moreover, it initializes the `Values_Cards` map with the values of the cards used in a game of blackjack.        *
     *                                                                                                                                                                     *
     * @note This constructor provides a way to create a ClassicSlot machine with default settings.                                                                        *
     *                                                                                                                                                                     *
     * @see Machine class for the base class constructor and initializations.                                                                                              *
     * @see Values_Cards for the map holding card values.                                                                                                                  *
     *                                                                                                                                                                     *
     * @exception None. This constructor does not throw exceptions.                                                                                                        *
     * @exceptsafe This constructor is exception-neutral. It offers no guarantees if an exception is thrown during initialization.                                         *
     *                                                                                                                                                                     *
     * @return None. Constructors do not return values.                                                                                                                    *
     ***********************************************************************************************************************************************************************/
    Blackjack();

    /*********************************************
     * @brief Destructor for Blackjack Machine   *
     *********************************************/
    ~Blackjack() override;

    /***************************************************************
     * @brief Function to print the Blackjack for testing purposes *
     ***************************************************************/
    [[maybe_unused]] [[maybe_unused]]void printMap() const; // no longer being used, but might be handy

    /*********************************************************************************************************************************************************************
     * @brief Adds a random card to a given hand in Blackjack.                                                                                                           *
     *                                                                                                                                                                   *
     * This member function of the `Blackjack` class is responsible for adding a random card to a player's hand. It selects a card randomly from the `Values_Cards`      *
     * container, which presumably holds the value of cards available in the game. The function uses a random number generator to select an index, and then              *
     * retrieves the card's value from `Values_Cards` based on this index. The selected card's value is then added to the player's hand.                                 *
     *                                                                                                                                                                   *
     * This function is a key component of the Blackjack game mechanics, enabling dynamic card distribution during the game.                                             *
     *                                                                                                                                                                   *
     * @note The function assumes that `Values_Cards` is already populated with the values of the cards available in the game.                                           *
     *                                                                                                                                                                   *
     * @see Values_Cards for the container holding card values.                                                                                                          *
     * @see randomNumberGeneratorInterval(int, int) for generating a random index.                                                                                       *
     *                                                                                                                                                                   *
     * @param hand A reference to a std::vector<int> representing the player's hand where the card value will be added.                                                  *
     *                                                                                                                                                                   *
     * @exception None. This function does not explicitly throw any exceptions. However, exceptions may be thrown by the methods it calls (like std::vector operations). *
     * @exceptsafe This function provides basic exception safety. If an exception is thrown, there are no side effects to the state of the 'hand' vector.                *
     *                                                                                                                                                                   *
     * @return void This function does not return a value but modifies the 'hand' vector by adding a new card value to it.                                               *
     *********************************************************************************************************************************************************************/
    void give_card(std::vector<int>& cards_map);

    /*******************************************************************************************************************************************************************
     * @brief Initiates a new game of Blackjack.                                                                                                                       *
     *                                                                                                                                                                 *
     * The `start_game` member function of the `Blackjack` class initiates a new round of the Blackjack game. It deals two cards each to the player and the dealer.    *
     * The dealing is done by calling the `give_card` function twice for both the player's hand (`Players_Hand`) and the dealer's hand (`Dealers_Hand`).               *
     * After dealing the cards, the function displays the player's hand and the first card of the dealer's hand, keeping the second card of the dealer hidden          *
     * (as per Blackjack rules).                                                                                                                                       *
     *                                                                                                                                                                 *
     * This function sets the stage for a round of Blackjack, ensuring that both the player and the dealer start with two cards each.                                  *
     *                                                                                                                                                                 *
     * @note The dealer's second card is not shown to the player, mimicking the traditional gameplay of Blackjack where one of the dealer's cards remains hidden.      *
     *                                                                                                                                                                 *
     * @see give_card() for the method used to deal cards to the hands.                                                                                                *
     * @see show_player_hand() for displaying the player's hand.                                                                                                       *
     *                                                                                                                                                                 *
     * @exception None. This method does not explicitly throw exceptions but relies on methods that might (e.g., vector operations in `give_card`).                    *
     * @exceptsafe This method is exception-neutral. It provides no exception safety guarantees and relies on the behavior of the methods it calls.                    *
     *                                                                                                                                                                 *
     * @return void. This function does not return a value but alters the state by dealing cards and displaying initial hands.                                         *
     *******************************************************************************************************************************************************************/
    void start_game();

    /*******************************************************************************************************************************************************************
     * @brief Displays the player's hand in the Blackjack game.                                                                                                        *
     *                                                                                                                                                                 *
     * This member function of the `Blackjack` class is responsible for displaying the cards currently in the player's hand. It iterates over the `Players_Hand`       *
     * vector, which contains the values of the cards held by the player, and prints each card value followed by a separator ('|'). This visual representation         *
     * helps the player to understand their current hand in the game.                                                                                                  *
     *                                                                                                                                                                 *
     * @note This function is typically called after cards are dealt or when the player needs to make a decision based on their hand.                                  *
     *                                                                                                                                                                 *
     * @see Players_Hand for the vector storing the player's card values.                                                                                              *
     *                                                                                                                                                                 *
     * @exception None. This function does not throw exceptions and performs simple iteration and output operations.                                                   *
     * @exceptsafe This function is exception-neutral and does not modify any game state.                                                                              *
     *                                                                                                                                                                 *
     * @return void. This function does not return a value but outputs the player's hand to the standard output.                                                       *
     *******************************************************************************************************************************************************************/
    void show_player_hand();

    /*******************************************************************************************************************************************************************
     * @brief Displays the dealer's hand in the Blackjack game.                                                                                                        *
     *                                                                                                                                                                 *
     * This member function of the `Blackjack` class is used to display the cards in the dealer's hand. It iterates over the `Dealers_Hand` vector, which holds        *
     * the values of the cards in the dealer's hand, and prints each card value followed by a separator ('|'). This function provides a visual representation          *
     * of the dealer's hand, which is essential for the player to see the dealer's current hand in the game.                                                           *
     *                                                                                                                                                                 *
     * @note This function is usually called at the end of a game round to reveal the dealer's full hand or when the dealer's hand changes during the game.            *
     *                                                                                                                                                                 *
     * @see Dealers_Hand for the vector storing the dealer's card values.                                                                                              *
     *                                                                                                                                                                 *
     *                                                                                                                                                                 *
     * @exception None. This function does not throw exceptions and performs simple iteration and output operations.                                                   *
     * @exceptsafe This function is exception-neutral and does not modify any game state.                                                                              *
     *                                                                                                                                                                 *
     * @return void. This function does not return a value but outputs the dealer's hand to the standard output.                                                       *
     *******************************************************************************************************************************************************************/
    void show_dealer_hand();

    /*******************************************************************************************************************************************************************
     * @brief Displays the current state of the Blackjack game.                                                                                                        *
     *                                                                                                                                                                 *
     * This member function of the `Blackjack` class shows the current state of the game by displaying both the player's and the dealer's hands. It calls              *
     * `show_player_hand` and `show_dealer_hand` to print each hand and then displays the total value of each hand using the `get_total` function.                     *
     *                                                                                                                                                                 *
     * @note This function is called throughout the game to update players on the current game state.                                                                  *
     *                                                                                                                                                                 *
     * @see show_player_hand()                                                                                                                                         *
     * @see show_dealer_hand()                                                                                                                                         *
     * @see get_total()                                                                                                                                                *
     *                                                                                                                                                                 *
     * @param None.                                                                                                                                                    *
     *                                                                                                                                                                 *
     * @exception None. This function does not throw exceptions and performs output operations.                                                                        *
     * @exceptsafe This function is exception-neutral and does not modify any game state.                                                                              *
     *                                                                                                                                                                 *
     * @return void. This function does not return a value but outputs the game state to the standard output.                                                          *
     *******************************************************************************************************************************************************************/
    void show_game();


    /*******************************************************************************************************************************************************************
     * @brief Randomly decides whether to hit or stay in the Blackjack game.                                                                                           *
     *                                                                                                                                                                 *
     * In the Blackjack game, this member function of the `Blackjack` class simulates a decision to either 'hit' (take another card) or 'stay' (end the turn).         *
     * The decision is made randomly using the `randomNumberGeneratorInterval` function, which returns 1 for 'hit' and 0 for 'stay'.                                   *
     *                                                                                                                                                                 *
     * @note This function is used to simulate the decision-making process in an automated game scenario.                                                              *
     *                                                                                                                                                                 *
     * @see randomNumberGeneratorInterval()                                                                                                                            *
     *                                                                                                                                                                 *
     * @param None.                                                                                                                                                    *
     * @return int - The decision result: 1 for 'hit', 0 for 'stay'.                                                                                                   *
     *                                                                                                                                                                 *
     * @exception None. This function does not throw exceptions.                                                                                                       *
     * @exceptsafe This function is exception-neutral and does not modify any game state.                                                                              *
     *                                                                                                                                                                 *
     * @return int - The decision result: 1 for 'hit', 0 for 'stay'.                                                                                                   *
     *******************************************************************************************************************************************************************/
    int  hit_or_stay();

    /*******************************************************************************************************************************************************************
     * @brief Simulates a round of the Blackjack game.                                                                                                                 *
     *                                                                                                                                                                 *
     * This function conducts a full simulation of a Blackjack game round. It starts the game, allows the player to make decisions (hit or stay), and simulates        *
     * the dealer's actions. The game continues until the player stays or either hand exceeds 21. The function concludes by determining the winner based on the        *
     * total values of the hands.                                                                                                                                      *
     *                                                                                                                                                                 *
     * @note This function is the core of the game's simulation, controlling the flow of a single round.                                                               *
     *                                                                                                                                                                 *
     * @see start_game()                                                                                                                                               *
     * @see get_total()                                                                                                                                                *
     * @see hit_or_stay()                                                                                                                                              *
     *                                                                                                                                                                 *
     *                                                                                                                                                                 *
     * @exception None. This function does not throw exceptions but relies on methods that might (e.g., vector operations).                                            *
     * @exceptsafe This function provides basic exception safety. If an exception is thrown, the game state remains unchanged.                                         *
     * @return bool - The result of the game: `true` if the player wins, `false` otherwise.                                                                            *
     *******************************************************************************************************************************************************************/
    bool simulate_game();

    /*******************************************************************************************************************************************************************
     * @brief Executes a game of Blackjack for a user.                                                                                                                 *
     *                                                                                                                                                                 *
     * This member function of the `Blackjack` class manages the interaction of a user with the Blackjack game. It checks the user's available money, simulates        *
     * a game round, and updates the user's status accordingly. The function also handles time tracking for the duration of the game and updates the machine's         *
     * temperature and usage statistics.                                                                                                                               *
     *                                                                                                                                                                 *
     * @note This function integrates the user's status and game mechanics, making it a central part of the gameplay experience.                                       *
     *                                                                                                                                                                 *
     * @see User class for user-related operations.                                                                                                                    *
     * @see simulate_game()                                                                                                                                            *
     * @see getElapsedTime()                                                                                                                                           *
     *                                                                                                                                                                 *
     * @param user Pointer to a `User` object representing the player.                                                                                                 *
     *                                                                                                                                                                 *
     * @exception None. This function does not throw exceptions but relies on methods that might.                                                                      *
     * @exceptsafe This function provides basic exception safety. If an exception is thrown, the user's state remains unchanged.                                       *
     *                                                                                                                                                                 *
     * @return bool - The outcome of the game: `true` if the player wins or the game is successfully completed, `false` otherwise.                                     *
     *******************************************************************************************************************************************************************/
    bool Play(User* user) override;

};

/*******************************************************************************************************************************************************************
 * @brief Calculates the total value of a hand in Blackjack.                                                                                                       *
 *                                                                                                                                                                 *
 * This function calculates the total value of a given hand in Blackjack. It iterates through the hand, summing the values of the cards. Special consideration     *
 * is given to the Ace card, which can be valued at either 1 or 11. If the hand contains an Ace and the total value does not exceed 21 when 10 is added,           *
 * the function treats the Ace as having a value of 11.                                                                                                            *
 *                                                                                                                                                                 *
 * @note This function is used to determine the current score of a player or dealer's hand.                                                                        *
 *                                                                                                                                                                 *
 * @param hand A std::vector<int> representing the hand, where each integer is the value of a card.                                                                *
 *                                                                                                                                                                 *
 * @exception None. This function does not throw exceptions.                                                                                                       *
 * @exceptsafe This function is exception-neutral and does not modify any game state.                                                                              *
 *                                                                                                                                                                 *
 * @return int The total value of the hand.                                                                                                                        *
 *******************************************************************************************************************************************************************/
int get_total(const std::vector<int> &hand);

#endif //CODE_BLACKJACK_H
