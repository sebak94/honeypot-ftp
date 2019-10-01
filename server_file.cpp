#include "server_file.h"
#include "server_file_error.h"
#include <stdint.h>
#include <string>

File::File(const std::string filename) {
    fi.open(filename, std::ios_base::in);
    if (fi.fail()) throw FileError("fopen failed");
}

std::istream& File::readLine(char *buf, size_t length) {
    return fi.getline(buf, length);
}

int File::error() {
    return fi.fail() || fi.bad();
}

File::~File() {
    fi.close();   
}
