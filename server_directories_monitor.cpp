#include "server_directories_monitor.h"
#include "server_lock.h"
#include <string>
#include <set>
#include <vector>

void DirectoriesMonitor::add(std::string &directory) {
    Lock l(m);
    directories.insert(directory);
}

size_t DirectoriesMonitor::remove(std::string &directory) {
    Lock l(m);
    return directories.erase(directory);
}

bool DirectoriesMonitor::exists(std::string &directory) {
    Lock l(m);
    return directories.count(directory);
}

void DirectoriesMonitor::getDirectories(std::vector<std::string> *direcs) {
    Lock l(m);
    for (std::set<std::string>::iterator it = directories.begin();
        it != directories.end(); it++) {
        direcs->push_back(*it);
    }
}
