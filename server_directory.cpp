#include "server_directory.h"
#include <string>

Directory::Directory(const std::string name): name(name) {}

std::string Directory::getName() const {
    return name;
}

bool Directory::operator<(const Directory &rd) const {
    return name < rd.name;
}

bool Directory::operator==(const Directory &d) const {
    return name == d.name;
}

Directory::~Directory() {}
