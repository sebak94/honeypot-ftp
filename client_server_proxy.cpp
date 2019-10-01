#include "client_server_proxy.h"
#include "common_socket_error.h"
#include "iostream"
#include "string.h"
#include <vector>
#include <string>

#define LIST_COMMAND "LIST\n"
#define LIST_COMMAND_END_CODE "226"
#define CODE_LENGTH 3

ServerProxy::ServerProxy(const char *hostname, const char *service) {
    try {
        skt.Connect(hostname, service);
    } catch(const SocketError &e) {
        std::cout << e.what() << "\n";
    }
}

std::string ServerProxy::getHelloMessage() {
    return receiveResponse();
}

bool ServerProxy::isMoreThanOneLineResponseCommand(std::string command) {
    size_t pos = command.find(" ");
    std::string name = command.substr(0, pos);
    return name == LIST_COMMAND;
}

std::string ServerProxy::executeCommand(std::string command) {
    sendCommand(command);
    if (isMoreThanOneLineResponseCommand(command)) {
        return receiveSeveralLinesResponse(LIST_COMMAND_END_CODE);
    }
    return receiveResponse();
}

void ServerProxy::sendCommand(std::string command) {
    const char *cmd = command.c_str();
    skt.Send(cmd, command.size());
}

std::string ServerProxy::receiveSeveralLinesResponse(std::string end_code) {
    std::vector<char> response;
    char first_three_chars[CODE_LENGTH + 1];
    char c;
    skt.Receive(first_three_chars, CODE_LENGTH);
    first_three_chars[CODE_LENGTH] = '\0';
    std::string last_three_chars(first_three_chars);
    while (last_three_chars != end_code) {
        response.push_back(c);
        skt.Receive(&c, 1);
        last_three_chars = std::string(response.end() - CODE_LENGTH,
            response.end());
    }
    while (c != '\n') {
        response.push_back(c);
        skt.Receive(&c, 1);
    }
    std::string str_resp(response.begin(), response.end());
    return first_three_chars + str_resp + "\n";
}

std::string ServerProxy::receiveResponse() {
    std::vector<char> response;
    char c;
    skt.Receive(&c, 1);
    while (c != '\n') {
        response.push_back(c);
        skt.Receive(&c, 1);
    }
    std::string str_resp(response.begin(), response.end());
    return str_resp + "\n";
}

ServerProxy::~ServerProxy() {}
