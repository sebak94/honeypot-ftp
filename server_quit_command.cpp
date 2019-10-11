#include "server_quit_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include <string>
#include <map>

QuitCommand::QuitCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string QuitCommand::execute(std::string &cmd_param, FTP &ftp, Client &cl) {
    return "221 " + config.at("quitSuccess") + "\n";
}
