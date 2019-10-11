#include "server_rmd_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include "server_directories_monitor.h"
#include <string>
#include <map>

RmdCommand::RmdCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string RmdCommand::execute(std::string &cmd_param, FTP &ftp,
    Client &cl) {
    if (!cl.isLoggedIn()) return executeFailure();
    return executeSuccess(cmd_param, ftp);
}

std::string RmdCommand::executeSuccess(std::string &cmd_param, FTP &ftp) {
    if (ftp.removeDirectory(cmd_param) == 1) {
        return "250 \"" + cmd_param + "\" " + config.at("rmdSuccess") + "\n";
    } else {
        return "550 " + config.at("rmdFailed") + "\n";
    }
}

std::string RmdCommand::executeFailure() {
    return "530 " + config.at("clientNotLogged") + "\n";
}
