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
