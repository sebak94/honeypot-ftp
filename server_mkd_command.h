#ifndef __MKD_COMMAND_H__
#define __MKD_COMMAND_H__

#include "server_command.h"
#include "server_ftp.h"
#include <string>
#include <map>

class MkdCommand: public Command {
    private:
    std::map<std::string, std::string> config;
    std::string executeSuccess(std::string &cmd_param, FTP &ftp);
    std::string executeFailure();

    public:
    MkdCommand(std::map<std::string, std::string> &config);
    virtual std::string execute(std::string &cmd_param, FTP &ftp, Client &cl) override;
};

#endif
