#include <iostream>
#include <string>
#include "client_server_proxy.h"
#include "common_socket_error.h"

#define SUCCESS 0

void run(const char *hostname, const char *service) {
    try {
        bool running = true;
        std::string str;
        ServerProxy sp(hostname, service);
        std::cout << sp.getHelloMessage();

        while (running && !std::getline(std::cin, str).eof()) {
            str += "\n";
            std::string response = sp.executeCommand(str);
            size_t pos = response.find(" ");
            std::string code = response.substr(0, pos);
            if (code == "221") running = false;
            std::cout << response;
            str = "";
        }
    } catch(const SocketError &e) {}
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cout << "./client <hostname> <service>";
        return SUCCESS;
    }
    run(argv[1], argv[2]);
    return SUCCESS;
}
