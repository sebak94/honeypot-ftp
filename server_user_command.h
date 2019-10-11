#ifndef __USER_COMMAND_H__
#define __USER_COMMAND_H__

#include "server_command.h"
#include "server_ftp.h"
#include <string>
#include <map>

class UserCommand: public Command {
    private:
    std::map<std::string, std::string> config;

    public:
    UserCommand(std::map<std::string, std::string> &config);
    virtual std::string execute(std::string &cmd_param, FTP &ftp,
        Client &cl) override;
};

#endif
