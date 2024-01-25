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

void beautify(const std::string& str) {
    int length = str.length();
    int padding = (50 - length) / 2;

    std::ostringstream oss;

    oss << "##################################################\n";
    oss << std::string(padding, '#');
    oss << str;
    // Complete the line with padding if it is an odd length
    if ((padding * 2 + length) < 50) {
        oss << std::string(padding + 1, '#');
    } else {
        oss << std::string(padding, '#');
    }
    oss << "\n##################################################\n";

    std::cout << oss.str();
}