#include "server_pass_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include <string>
#include <map>

PassCommand::PassCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string PassCommand::execute(std::string &cmd_param, FTP &ftp, Client &cl) {
    if (config.at("user") == cl.last_command_param &&
        config.at("password") == cmd_param) {
        return executeSuccess(cl);
    }
    return executeFailure();
}

std::string PassCommand::executeSuccess(Client &cl) {
    cl.login();
    return "230 " + config.at("loginSuccess") + "\n";
}

std::string PassCommand::executeFailure() {
    return "530 " + config.at("loginFailed") + "\n";
}
