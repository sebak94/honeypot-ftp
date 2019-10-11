#include "server_unknown_command.h"
#include "server_ftp.h"
#include <string>

UnknownCommand::UnknownCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string UnknownCommand::execute(std::string &cmd_param, FTP &ftp, Client &cl) {
    return "221 " + config.at("unknownCommand") + "\n";
}
