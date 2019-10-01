#ifndef __SERVER_PROXY_H__
#define __SERVER_PROXY_H__

#include "common_socket.h"
#include "string"
#include "map"

class ServerProxy {
    private:
    Socket skt;

    void sendCommand(std::string command);
    std::string receiveResponse();
    std::string receiveSeveralLinesResponse(std::string end_code);
    bool isMoreThanOneLineResponseCommand(std::string command);

    public:
    ServerProxy(const char *hostname, const char *service);
    std::string getHelloMessage();
    std::string executeCommand(std::string command);
    ~ServerProxy();
};

#endif
