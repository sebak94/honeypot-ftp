#include "server_help_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include "server_directories_monitor.h"
#include <string>
#include <map>

HelpCommand::HelpCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string HelpCommand::execute(std::string &cmd_param, FTP &ftp,
    Client &cl) {
    if (!cl.isLoggedIn()) return executeFailure();
    return executeSuccess();
}

std::string HelpCommand::executeSuccess() {
    return "214 " + config.at("commands") + "\n";
}

std::string HelpCommand::executeFailure() {
    return "530 " + config.at("clientNotLogged") + "\n";
}
