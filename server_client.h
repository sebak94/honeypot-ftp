#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>

class Client {
    private:
    const int id;
    bool is_logged_in;

    public:
    explicit Client(int id);
    bool isLoggedIn();
    void login();
    std::string last_command;
    std::string last_command_param;
};

#endif
