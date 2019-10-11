#ifndef __LIST_COMMAND_H__
#define __LIST_COMMAND_H__

#include "server_command.h"
#include "server_ftp.h"
#include <string>
#include <map>

class ListCommand: public Command {
    private:
    std::map<std::string, std::string> config;
    std::string executeSuccess(FTP &ftp);
    std::string executeFailure(Client &cl);

    public:
    ListCommand(std::map<std::string, std::string> &config);
    virtual std::string execute(std::string &cmd_param, FTP &ftp, Client &cl) override;
};

#endif
