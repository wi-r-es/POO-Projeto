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

class Machine;

/******************************************************************************
 * Machine ADT class and variables description                                *
 * d_id                 -> Unique identifier (ID) for each user (client).     *
 * d_name               -> User's Full name.                                  *
 * d_city               -> User's city.                                       *
 * d_age                -> User's age.                                        *
 * d_time_spent         -> User's time spent inside the casino                *
 * d_prizes_won         -> User's total amount of prizes won.                 *
 ******************************************************************************/
class User {
private:
    char d_id[10]; // confirmar se pode usar char ou se temos de usar strings, this makes life easier tho
    std::string d_name;
    std::string d_city;
    int d_age;
    int d_time_spent;
    int d_prizes_won;
    int playing:1; //bitfield to tell if the user is playing or not
public:
    /*******************************************************************************
     * @brief Constructor for User                                                 *
     * @param id     -> an string representing the ID of the user                  *
     * @param name   -> a string representing the full name of the user.           *
     * @param city   -> a string representing the name of the city of the user.    *
     * @param age    -> an int representing the age of the user                    *
     *******************************************************************************/
    User(char *id, std::string name, std::string city, int age);

    User();

    /***********************************
     * @brief Destructor for User      *
     ***********************************/
    virtual ~User();


    const char *getId() const;

    const std::string &getName() const;

    void setName(const std::string &dName);

    const std::string &getCity() const;

    void setCity(const std::string &dCity);

    int getAge() const;

    void setAge(int dAge);

    int getTimeSpent() const;

    void setTimeSpent(int dTimeSpent);

    int getPrizesWon() const;

    void setPrizesWon(int dPrizesWon);

    int getPlaying() const;

    void setPlaying(int playing);

    /***************************************************************************
     * @brief Function to simulate the user using a machine
     * USe it to register the playing fact perhaps ?
     */
    void playGame(Machine *Mac);

};


#endif //CODE_USER_H
