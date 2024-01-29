//
// Created on 06/11/23.
//

/*******************************************************************************
 *  @file User.h                                                               *
 *  @brief Class prototypes for User ADT Structure/Class                       *
 *                                                                             *
 *  This contains the prototypes for the managing of User and its fields.      *
 *                                                                             *
 *******************************************************************************/

#ifndef CODE_USER_H
#define CODE_USER_H
#include <string>
#include <cstring>
#include <utility>
#include <cstdio>
#include <chrono>


/*****************************************************************************************
 * User ADT class and variables description                                              *
 *                                                                                       *
 * d_id                 -> Unique identifier (ID) for each user (client).                *
 * d_name               -> User's Full name.                                             *
 * d_city               -> User's city.                                                  *
 * d_age                -> User's age.                                                   *
 * d_money              -> User's money                                                  *
 * d_time_spent         -> User's time spent inside the casino.                          *
 * d_prizes_won         -> User's total amount of prizes won.                            *
 * d_bets                 -> User's bet within a game round.                               *
 * d_profit               -> User's profit inside the casino.                              *
 * d_debt                 -> User's debt to the casino.                                    *
 * count_plays_no_money -> Counter for number of times user tried to play without money. *
 * playing              -> Flag to control whether user is playing. \NOT USED            *
 *****************************************************************************************/
class User {
private:

    char d_id[10];
    std::string d_name;
    std::string d_city;
    int d_age;
    float d_money;
    std::chrono::seconds d_time_spent;
    float d_prizes_won;
    int d_bets;
    int d_profit;
    float d_debt;
    int count_plays_no_money;
    [[maybe_unused]]unsigned int playing : 1; //bitfield to tell if the user is playing or not

public:

    /*******************************************************************************
     * @brief Constructor for User                                                 *
     * @param id     -> an string representing the ID of the user                  *
     * @param name   -> a string representing the full name of the user.           *
     * @param city   -> a string representing the name of the city of the user.    *
     * @param age    -> an int representing the age of the user                    *
     * @exceptsafe none - Shall not throw exceptions                               *
     * @return Newly created User object                                           *
     *******************************************************************************/
    User(char *id, std::string name, std::string city, int age);

    /**************************************************
     * @brief Destructor for User                     *
     * @exceptsafe none - Shall not throw exceptions  *
     * @return NONE                                   *
     **************************************************/
    virtual ~User();

    /***************************************************
     * @brief Getter for user Bets                     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return Number of bets.                         *
     ***************************************************/
    [[nodiscard]] int getBets() const;

    /***************************************************
     * @brief Increment user number of bets            *
     * @exceptsafe none - Shall not throw exceptions   *
     * @param bets -> integer to add to user bets      *
     * @return None.                                   *
     ***************************************************/
    void incBets(int bets);

    /***************************************************
     * @brief Getter for user ID                       *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return User's ID.                              *
     ***************************************************/
    [[nodiscard]] const char *getId() const;

    /****************************************************
     * @brief Getter for user Name                      *
     * @exceptsafe none - Shall not throw exceptions    *
     * @return User's name.                             *
     ****************************************************/
    [[nodiscard]] const std::string &getName() const;

    /***************************************************
     * @brief Setter for user Name                     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @param dName -> name to set to                  *
     * @return None.                                   *
     ***************************************************/
    [[maybe_unused]]void setName(const std::string &dName);

    /***************************************************
     * @brief Getter for user city                     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return User's city.                            *
     ***************************************************/
    [[nodiscard]] const std::string &getCity() const;

    /***************************************************
     * @brief Setter for user city                     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @param dCity -> string of city to set to        *
     * @return None.                                   *
     ***************************************************/
    [[maybe_unused]]void setCity(const std::string &dCity);

    /***************************************************
     * @brief Getter for user age                      *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return User's age.                             *
     ***************************************************/
    [[nodiscard]] int getAge() const;

    /***************************************************
     * @brief Setter for user age                      *
     * @exceptsafe none - Shall not throw exceptions   *
     * @param dAge -> age to set to                    *
     * @return None.                                   *
     ***************************************************/
    [[maybe_unused]]void setAge(int dAge);

    /***************************************************
     * @brief Getter for user time spent in casino     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return User's time spent in casino.            *
     ***************************************************/
    [[nodiscard]] long getTimeSpent() const;

    /****************************************************************
     * @brief Increment the user time spent in casino               *
     *                                                              *
     *        Adds time to the users time spent inside the casino   *
     *                                                              *
     * @exceptsafe none - Shall not throw exceptions                *
     * @param dTimeSpent -> chrono::seconds of user's time spent    *
     * @return None.                                                *
     ****************************************************************/
    void incTimeSpent(std::chrono::seconds dTimeSpent);

    /****************************************************
     * @brief Getter for user acquired prizes           *
     * @exceptsafe none - Shall not throw exceptions    *
     * @return User's acquired prizes.                  *
     ****************************************************/
    [[nodiscard]] float getPrizesWon() const;

    /****************************************************************
     * @brief Increment the user acquired prizes                    *
     *                                                              *
     *        Adds more prizes (money) to the users prizes          *
     *                                                              *
     * @exceptsafe none - Shall not throw exceptions                *
     * @param dPrizesWon -> money to add to user's bets               *
     * @return None.                                                *
     ****************************************************************/
    void incPrizesWon(float dPrizesWon);

    /***************************************************
     * @brief Getter for user playing flag             *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return User's flag for playing status.         *
     ***************************************************/
    [[maybe_unused]] [[nodiscard]] int getPlaying() const; //not used

    /***************************************************
     * @brief Setter for user playing flag             *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return None.                                   *
     ***************************************************/
    [[maybe_unused]]void setPlaying(int playing); //not used

    /***************************************************
     * @brief Getter for user money                    *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return User's money.                           *
     ***************************************************/
    [[nodiscard]] float getMoney() const;

    /***************************************************
     * @brief Setter for user money                    *
     * @exceptsafe none - Shall not throw exceptions   *
     * @param money -> user's money to set to          *
     * @return None.                                   *
     ***************************************************/
    void setMoney(float money);

    /**********************************************************************
     * @brief Increments user attempts for trying to play without money   *
     * @exceptsafe none - Shall not throw exceptions                      *
     * @return None.                                                      *
     **********************************************************************/
    void incAttempts();

    /**********************************************************************
     * @brief Reset user attempts for trying to play without money        *
     * @exceptsafe none - Shall not throw exceptions                      *
     * @return None.                                                      *
     **********************************************************************/
    void resetAttempts();

    /******************************************************************
     * @brief Getter for user attempts trying to play without money   *
     * @exceptsafe none - Shall not throw exceptions                  *
     * @return None.                                                  *
     ******************************************************************/
    [[nodiscard]] int getAttempts() const;

    /************************************************************
     * @brief Add bet to user                                   *
     * @exceptsafe none - Shall not throw exceptions            *
     * @param amountOfDebt -> Amount of bet to be added to user *
     * @return None.                                            *
     ************************************************************/
    void addDebt(float amountOfDebt);

    /***************************************************
     * @brief Getter for user debt                     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return User's bet.                             *
     ***************************************************/
    [[nodiscard]] float getDebt() const;

    /***************************************************
     * @brief Converts a user object into a string     *
     * @exceptsafe none - Shall not throw exceptions   *
     * @return a String representation of the object   *
     ***************************************************/
    std::string toString();


};


#endif //CODE_USER_H
