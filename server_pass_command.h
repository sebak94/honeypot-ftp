#ifndef __PASS_COMMAND_H__
#define __PASS_COMMAND_H__

#include "server_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include <string>
#include <map>

class PassCommand: public Command {
    private:
    std::map<std::string, std::string> config;
    std::string executeSuccess(Client &cl);
    std::string executeFailure();

    public:
    PassCommand(std::map<std::string, std::string> &config);
    virtual std::string execute(std::string &cmd_param, FTP &ftp, Client &cl) override;
};

#endif
