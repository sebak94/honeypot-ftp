#include "server_syst_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include <string>
#include <map>

SystCommand::SystCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string SystCommand::execute(std::string &cmd_param, FTP &ftp, Client &cl) {
    if (!cl.isLoggedIn()) return executeFailure(cl);
    return executeSuccess();
}

std::string SystCommand::executeSuccess() {
    return "215 " + config.at("systemInfo") + "\n";
}

std::string SystCommand::executeFailure(Client &cl) {
    cl.last_command = "";
    cl.last_command_param = "";
    return "530 " + config.at("clientNotLogged") + "\n";
}
