#ifndef __DIRECTORIES_MONITOR_H__
#define __DIRECTORIES_MONITOR_H__

#include <mutex>
#include <string>
#include <set>
#include <vector>

class DirectoriesMonitor {
    private:
    std::mutex m;
    std::set<std::string> directories;

    public:
    void add(std::string &directory);
    size_t remove(std::string &directory);
    bool exists(std::string &directory);
    void getDirectories(std::vector<std::string> *direcs);
};

#endif
