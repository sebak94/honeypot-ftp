#include "server_pwd_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include "server_directories_monitor.h"
#include <string>
#include <map>

PwdCommand::PwdCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string PwdCommand::execute(std::string &cmd_param, FTP &ftp,
    Client &cl) {
    if (!cl.isLoggedIn()) return executeFailure();
    return executeSuccess();
}

std::string PwdCommand::executeSuccess() {
    return "257 " + config.at("currentDirectoryMsg") + "\n";
}

std::string PwdCommand::executeFailure() {
    return "530 " + config.at("clientNotLogged") + "\n";
}
