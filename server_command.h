#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "server_client.h"
#include "server_ftp.h"
#include <string>

class Command {
    public:
    virtual std::string execute(std::string &cmd_param, FTP &ftp, Client &cl) = 0;
};

#endif
