#include "server_mkd_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include "server_directories_monitor.h"
#include <string>
#include <map>

MkdCommand::MkdCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string MkdCommand::execute(std::string &cmd_param, FTP &ftp,
    Client &cl) {
    if (!cl.isLoggedIn()) return executeFailure();
    return executeSuccess(cmd_param, ftp);
}

std::string MkdCommand::executeSuccess(std::string &cmd_param, FTP &ftp) {
    if (ftp.addDirectory(cmd_param)) {
        return "257 \"" + cmd_param + "\" " + config.at("mkdSuccess") + "\n";
    } else {
        return "550 " + config.at("mkdFailed") + "\n";
    }
}

std::string MkdCommand::executeFailure() {
    return "530 " + config.at("clientNotLogged") + "\n";
}
