#include "server_client_th.h"
#include "common_socket.h"
#include "common_socket_error.h"
#include "iostream"
#include "vector"
#include "string"

ClientTh::ClientTh(Socket *peer, FTP *ftp): keep_talking(true),
    is_running(true), peer(peer), ftp(ftp) {
    std::string hello = ftp->newClientMessage();
    sendResponse(hello);
}

void ClientTh::run() {
    while (keep_talking) {
        try {
            bool should_stop_after_send = false;
            std::vector<char> v_cmd;
            receiveCommand(v_cmd);
            std::string str_cmd(v_cmd.begin(), v_cmd.end());
            std::string response = handleCommand(str_cmd,
                &should_stop_after_send);
            sendResponse(response);
            if (should_stop_after_send) stop();
        } catch(const SocketError &e) {
            keep_talking = false;
            std::cout << e.what() << "\n";
        }
    }

    is_running = false;
}

std::string ClientTh::handleCommand(std::string &cmd,
    bool *should_stop_after_send) {
    size_t pos = cmd.find(" ");
    std::string name = cmd.substr(0, pos);
    std::string param;

    if (pos >= cmd.length() - 1) param = "";
    else
        param = cmd.substr(pos + 1);

    std::string response = ftp->executeCommand(name, param, me);
    if (name == "QUIT") *should_stop_after_send = true;
    return response;
}

void ClientTh::receiveCommand(std::vector<char> &command) {
    char c;
    peer->Receive(&c, 1);
    while (c != '\n') {
        command.push_back(c);
        peer->Receive(&c, 1);
    }
}

void ClientTh::sendResponse(std::string &response) {
    const char *resp = response.c_str();
    peer->Send(resp, response.length());
}

void ClientTh::stop() {
    keep_talking = false;
    peer->Release();
}

bool ClientTh::isDead() {
    return !is_running;
}

ClientTh::~ClientTh() {}
