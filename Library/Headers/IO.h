//
// Created on 18/11/23.
//

#ifndef CODE_IO_H
#define CODE_IO_H

#include <string>
#include <fstream>

using namespace std;

#ifdef _WIN32
ifstream clients_file  { "..\\..\\Files\\I\\pessoas.txt" };
#else
ifstream clients_file { "../../Files/I/pessoas.txt" } ;
#endif

ifstream open(const char* path, ios_base::openmode mode = ios_base::in);

#endif //CODE_IO_H
