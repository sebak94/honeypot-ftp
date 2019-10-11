#include "server_user_command.h"
#include "server_ftp.h"

UserCommand::UserCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string UserCommand::execute(std::string &cmd_param, FTP &ftp, Client &cl) {
    cl.last_command = "USER";
    cl.last_command_param = cmd_param;
    return "331 " + config.at("passRequired") + "\n";
}
