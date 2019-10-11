#include "server_ftp.h"
#include "server_acceptor_th.h"
#include "common_socket_error.h"
#include <iostream>
#include <string>

#define SUCCESS 0

void run(const char* service, std::string config_file) {
    try {
        FTP ftp(config_file);
        AcceptorTh acceptor_th(service, &ftp);
        acceptor_th.start();
        while (getc(stdin) != 'q') {}
        acceptor_th.stop();
        acceptor_th.join();
    } catch(const SocketError &e) {
        std::cout << e.what() << "\n";
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cout << "./server <service> <config_file>\n";
        return SUCCESS;
    }
    run(argv[1], argv[2]);
    return SUCCESS;
}
