#include "server_directories_monitor.h"
#include "server_lock.h"
#include <string>
#include <set>

void DirectoriesMonitor::add(std::string directory) {
    Lock l(m);
    directories.insert(directory);
}

size_t DirectoriesMonitor::remove(std::string directory) {
    Lock l(m);
    return directories.erase(directory);
}

bool DirectoriesMonitor::exist(std::string directory) {
    return directories.count(directory);
}

size_t DirectoriesMonitor::size() {
    Lock l(m);
    return directories.size();
}

std::set<std::string>::iterator DirectoriesMonitor::begin() {
    return directories.begin();
}
std::set<std::string>::iterator DirectoriesMonitor::end() {
    return directories.end();
}
