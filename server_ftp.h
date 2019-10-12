#ifndef __FTP_H__
#define __FTP_H__

#include "server_directories_monitor.h"
#include "server_client.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class FTP {
    private:
    std::map<std::string, std::string> config;
    DirectoriesMonitor directories;

    public:
    explicit FTP(std::string config_file);
    std::string newClientMessage();
    std::string executeCommand(std::string &name, std::string &param,
        Client &cl);
    bool addDirectory(std::string direc);
    size_t removeDirectory(std::string direc);
    void getDirectories(std::vector<std::string> *direcs);
    ~FTP();
};

#endif
