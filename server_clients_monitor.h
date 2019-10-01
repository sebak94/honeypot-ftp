#ifndef __CLIENTS_MONITOR_H__
#define __CLIENTS_MONITOR_H__

#include <mutex>
#include <map>
#include "server_client.h"

class ClientsMonitor {
    private:
    std::mutex m;
    std::map<int, Client*> clients;

    public:
    Client* at(int key);
    void add(int key, Client *value);
    Client* remove(int key);
    bool exist(int key);
    size_t size();
    std::map<int, Client*>::iterator begin();
    std::map<int, Client*>::iterator end();
};

#endif
