#include "server_clients_monitor.h"
#include "server_lock.h"
#include <map>
#include <utility>
#include <stdexcept>

Client* ClientsMonitor::at(int key) {
    Lock l(m);
    return clients.at(key);
}

void ClientsMonitor::add(int key, Client *value) {
    Lock l(m);
    clients.insert(std::pair<int, Client*>(key, value));
}

Client* ClientsMonitor::remove(int key) {
    Lock l(m);
    Client *cl = clients.at(key);
    clients.erase(key);
    return cl;
}

bool ClientsMonitor::exist(int key) {
    return clients.count(key);
}

std::map<int, Client*>::iterator ClientsMonitor::begin() {
    return clients.begin();
}

std::map<int, Client*>::iterator ClientsMonitor::end() {
    return clients.end();
}
