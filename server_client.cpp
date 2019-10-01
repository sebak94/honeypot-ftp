#include "server_client.h"
#include <string>

Client::Client(int id): id(id), is_logged_in(false) {
    last_command = "";
    last_command_param = "";
}

bool Client::isLoggedIn() {
    return is_logged_in;
}

void Client::login() {
    is_logged_in = true;
}
