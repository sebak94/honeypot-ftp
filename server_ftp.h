#ifndef __FTP_H__
#define __FTP_H__

#include <map>
#include <string>
#include "server_directories_monitor.h"
#include "server_clients_monitor.h"

class FTP {
    private:
    std::map<std::string, std::string> config;
    DirectoriesMonitor directories;
    ClientsMonitor clients;

    std::string callCorrectMethod(std::string name, std::string param,
        Client *cl);
    std::string user(std::string user, Client *cl);
    std::string pass(std::string pass, Client *cl);
    std::string syst(Client *cl);
    std::string list(Client *cl);
    std::string help(Client *cl);
    std::string pwd(Client *cl);
    std::string mkd(std::string direc, Client *cl);
    std::string rmd(std::string direc, Client *cl);
    std::string quit();
    std::string clientNotLogged(Client *cl);

    public:
    explicit FTP(std::string config_file);
    void addNewClient(int fd);
    void removeClient(int fd);
    std::string newClientMessage();
    std::string executeCommand(std::string &name, std::string &param,
        int client_fd);
    ~FTP();
};

#endif
