#ifndef __SYST_COMMAND_H__
#define __SYST_COMMAND_H__

#include "server_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include <string>
#include <map>

class SystCommand: public Command {
    private:
    std::map<std::string, std::string> config;
    std::string executeSuccess();
    std::string executeFailure(Client &cl);

    public:
    SystCommand(std::map<std::string, std::string> &config);
    virtual std::string execute(std::string &cmd_param, FTP &ftp, Client &cl) override;
};

#endif
