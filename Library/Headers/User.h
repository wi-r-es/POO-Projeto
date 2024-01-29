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
 * bets                 -> User's bet within a game round.                               *
 * profit               -> User's profit inside the casino.                              *
 * debt                 -> User's debt to the casino.                                    *
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
    int d_prizes_won;
    int bets;
    int profit;
    float debt;
    int count_plays_no_money;
    [[maybe_unused]]unsigned int playing : 1; //bitfield to tell if the user is playing or not
public:

    /*******************************************************************************
     * @brief Constructor for User                                                 *
     * @param id     -> an string representing the ID of the user                  *
     * @param name   -> a string representing the full name of the user.           *
     * @param city   -> a string representing the name of the city of the user.    *
     * @param age    -> an int representing the age of the user                    *
     * @exceptsafe none - Shall not throw exceptions
     * @return Newly created User object
     *******************************************************************************/
    User(char *id, std::string name, std::string city, int age);

    User();
    /***********************************
     * @brief Destructor for User      *
     * @exceptsafe none - Shall not throw exceptions
     * @return NONE
     ***********************************/
    virtual ~User();

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
    int getBets() const;

    void setBets(int bets);

    const char *getId() const;

    const std::string &getName() const;

    void setName(const std::string &dName);

    const std::string &getCity() const;

    void setCity(const std::string &dCity);

    int getAge() const;

    void setAge(int dAge);

    long getTimeSpent() const;

    void setTimeSpent(std::chrono::seconds dTimeSpent);

    int getPrizesWon() const;

    void setPrizesWon(float dPrizesWon);

    int getPlaying() const;

    void setPlaying(int playing);

    float getMoney() const;

    void setMoney(float money);

    void incAttempts();
    void resetAttempts();
    int getAttempts() const;

    void addDebt(float amountOfDebt);
    float getDebt() const;

    std::string toString();


};


#endif //CODE_USER_H
