#include "server_ftp.h"
#include "server_file.h"
#include "server_file_error.h"
#include "server_client.h"
#include "server_command_factory.h"
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <utility>

FTP::FTP(std::string config_file) {
    try {
        File f(config_file);
        std::string line;

        while (!f.readLine(&line).eof()) {
            size_t pos = line.find("=");
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            config.insert(std::pair<std::string, std::string>(key, value));
        }
    } catch(const FileError &e) {
        std::cout << e.what() << "\n";
    }
}

std::string FTP::executeCommand(std::string &name, std::string &param,
    Client &cl) {
    std::shared_ptr<Command> cmd = CommandFactory::GetCommand(name, config);
    return cmd->execute(param, *this, cl);
}

std::string FTP::newClientMessage() {
    return "220 " + config.at("newClient") + "\n";
}

bool FTP::addDirectory(std::string direc) {
    if (directories.exists(direc)) return false;
    directories.add(direc);
    return true;
}

size_t FTP::removeDirectory(std::string direc) {
    return directories.remove(direc);
}

std::set<std::string>::iterator FTP::directoriesIteratorBegin() {
    return directories.begin();
}

std::set<std::string>::iterator FTP::directoriesIteratorEnd() {
    return directories.end();
}

FTP::~FTP() {}
