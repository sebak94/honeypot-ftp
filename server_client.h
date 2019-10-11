#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>

class Client {
    private:
    bool is_logged_in;

    public:
    Client();
    bool isLoggedIn();
    void login();
    std::string last_command;
    std::string last_command_param;
};

#endif
