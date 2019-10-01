#ifndef __DIRECTORIES_MONITOR_H__
#define __DIRECTORIES_MONITOR_H__

#include <mutex>
#include <string>
#include <set>

class DirectoriesMonitor {
    private:
    std::mutex m;
    std::set<std::string> directories;

    public:
    void add(std::string directory);
    size_t remove(std::string directory);
    bool exist(std::string directory);
    std::set<std::string>::iterator begin();
    std::set<std::string>::iterator end();
};

#endif
