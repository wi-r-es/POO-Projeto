//
// Created on 18/11/23.
//

#include "Headers/IO.h"
#include "Headers/utils.h"

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

void beautify(const std::string& str, const char ch) {
    int length = str.length();
    int padding = (50 - length) / 2;
    std::ostringstream oss;
    auto border = new std::string(50, ch );
    auto paddingStr = new std::string(padding, ch);

    oss << *border <<"\n";
    oss << *paddingStr;
    oss << str;
    // Complete the line with padding if it is an odd length
    if ((padding * 2 + length) < 50) {
        oss << std::string(padding + 1, ch);
    } else {
        oss << *paddingStr;
    }
    oss << "\n" << *border << "\n\n";
    std::cout << oss.str();
    //to prevent leaks
    delete border; delete paddingStr;
}

void printTime(const time_t& _time) {
    std::cout << "\n\t\t\t\t TIME = " << asctime(localtime(&_time));
}

void List_Specific_Containers(const std::vector<Machine *>& container, std::list<Machine *> &l,std::ostream &f){
    for (const auto &machine : container) {
        f << machine->toString() << '\n';
        l.push_back(machine);

    }
}
