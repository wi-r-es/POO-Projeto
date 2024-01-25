//
// Created on 18/11/23.
//

#ifndef CODE_IO_H
#define CODE_IO_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

#ifdef _WIN32
ifstream clients_file  { "..\\..\\Files\\I\\pessoas.txt" };
#else
//ifstream clients_file { "../../Files/I/pessoas.txt" } ;

#endif

ifstream open(const char* path, ios_base::openmode mode = ios_base::in);


void logging(const std::string& filename, const std::string& funcname, const std::string& info);


void beautify(const std::string& str, char ch = '#');
void printTime(const time_t& _time);


#endif //CODE_IO_H
