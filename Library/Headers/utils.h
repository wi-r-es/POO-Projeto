//
// Created on 25/01/24.
//

#ifndef CODE_UTILS_H
#define CODE_UTILS_H

#include <utility>
#include <random>
#include <chrono>
#include <thread>
#include <list>
#include <type_traits>

#include "Machine.h"

int randomNumberGeneratorInterval(int x, int y);
void Wait(int seconds);
std::chrono::seconds getElapsedTime(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);

namespace MachineUtils{
    /** specific content for C++ 17, for C++ 20 concepts can be used **/
    /**  Helper template to check for toString method **/
    template<typename T, typename = std::void_t<>>
    struct has_toString_method : std::false_type {
    };

    template<typename T>
    struct has_toString_method<T, std::void_t<decltype(std::declval<T>().toString())>> : std::true_type {
    };

    template<typename Container>
    void printElements(const Container &container) {
        /** Check if the container's value_type is Machine **/
        static_assert(std::is_same_v<typename Container::value_type, Machine>,
                      "Container does not contain Machine objects");

        /** Check if Machine has a toString method **/
        static_assert(has_toString_method<Machine>::value, "Machine does not have a toString method");

        for (const auto &element: container) {
            std::cout << element.toString() << std::endl;
        }
    }

}


#endif //CODE_UTILS_H
