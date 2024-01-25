//
// Created on 18/11/23.
//

#include "Headers/IO.h"

ifstream open(const char* path, ios_base::openmode mode){
    ifstream file{ path, mode };
    if(!file.is_open()) {
        string err{ "Unable to open file "};
        err.append(path);
        throw runtime_error{ err };
    }
    file.exceptions(ifstream::badbit);
    return file;
}

void logging(const std::string& filename, const std::string& funcname, const std::string& info) {
    if (funcname.empty() || info.empty())
        return;
    try {
        std::ofstream file{filename, std::ios::app};
        if (!file.is_open())
            throw std::runtime_error("Unable to open file: " + filename);
        file << __DATE__ << "," << __TIME__ << ",[EXECUTING_FUNCTION]: " << funcname << ",[SHORT-BRIEF]: " << info
             << std::endl;

    } catch (const std::runtime_error &e) {
        std::cerr << "An error occurred: " << e.what() << '\n';
        system("pwd");
    }
}