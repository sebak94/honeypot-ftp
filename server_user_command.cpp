#include "server_user_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include <string>
#include <map>

UserCommand::UserCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string UserCommand::execute(std::string &cmd_param, FTP &ftp, Client &cl) {
    cl.last_command = "USER";
    cl.last_command_param = cmd_param;
    return "331 " + config.at("passRequired") + "\n";
}
