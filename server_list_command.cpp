#include "server_list_command.h"
#include "server_ftp.h"
#include "server_client.h"
#include "server_directories_monitor.h"
#include <string>
#include <map>
#include <set>
#include <vector>

ListCommand::ListCommand(std::map<std::string, std::string> &config):
    config(config) {}

std::string ListCommand::execute(std::string &cmd_param, FTP &ftp,
    Client &cl) {
    if (!cl.isLoggedIn()) return executeFailure(cl);
    return executeSuccess(ftp);
}

std::string ListCommand::executeSuccess(FTP &ftp) {
    std::string response = "150 " + config.at("listBegin") + "\n";
    std::vector<std::string> directories;
    ftp.getDirectories(&directories);
    for (std::vector<std::string>::iterator it = directories.begin();
        it != directories.end(); it++) {
        std::string line = "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 "
            + *it + "\n";
        response += line;
    }
    response += "226 " + config.at("listEnd") + "\n";
    return response;
}

std::string ListCommand::executeFailure(Client &cl) {
    cl.last_command = "";
    cl.last_command_param = "";
    return "530 " + config.at("clientNotLogged") + "\n";
}
