#ifndef __UNKNOWN_COMMAND_H__
#define __UNKNOWN_COMMAND_H__

#include "server_command.h"
#include <string>
#include <map>

class UnknownCommand: public Command {
    private:
    std::map<std::string, std::string> config;

    public:
    UnknownCommand(std::map<std::string, std::string> &config);
    virtual std::string execute(std::string &cmd_param, FTP &ftp,
        Client &cl) override;
};

#endif
