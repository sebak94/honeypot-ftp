#ifndef __QUIT_COMMAND_H__
#define __QUIT_COMMAND_H__

#include "server_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include <string>
#include <map>

class QuitCommand: public Command {
    private:
    std::map<std::string, std::string> config;

    public:
    QuitCommand(std::map<std::string, std::string> &config);
    virtual std::string execute(std::string &cmd_param, FTP &ftp,
        Client &cl) override;
};

#endif
