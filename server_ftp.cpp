#include "server_ftp.h"
#include "server_file.h"
#include "server_file_error.h"
#include "server_client.h"
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <utility>

FTP::FTP(std::string config_file) {
    try {
        File f(config_file);
        char line[BUF_LEN];

        while (!f.readLine(line, BUF_LEN).eof()) {
            std::string lineStr = std::string(line);
            size_t pos = lineStr.find("=");
            std::string key = lineStr.substr(0, pos);
            std::string value = lineStr.substr(pos + 1);
            config.insert(std::pair<std::string, std::string>(key, value));
        }
    } catch(const FileError &e) {
        std::cout << e.what() << "\n";
    }
}

void FTP::addNewClient(int fd) {
    Client *cl = new Client(fd);
    clients.add(fd, cl);
}

void FTP::removeClient(int fd) {
    if (clients.exist(fd)) delete clients.remove(fd);
}

std::string FTP::executeCommand(std::string &name, std::string &param,
    int client_fd) {
    Client *cl = clients.at(client_fd);

    return callCorrectMethod(name, param, cl);
}

std::string FTP::callCorrectMethod(std::string command_name,
    std::string command_param, Client *cl) {
    if (cl->last_command == "USER" && command_name != "PASS") {
        return clientNotLogged(cl);
    }
    if (command_name == "QUIT") return quit();
    if (command_name == "USER") return user(command_param, cl);
    if (command_name == "PASS") return pass(command_param, cl);
    if (command_name == "SYST") return syst(cl);
    if (command_name == "LIST") return list(cl);
    if (command_name == "HELP") return help(cl);
    if (command_name == "PWD") return pwd(cl);
    if (command_name == "MKD") return mkd(command_param, cl);
    if (command_name == "RMD") return rmd(command_param, cl);
    return "530 " + config.at("unknownCommand") + "\n";
}

std::string FTP::newClientMessage() {
    return "220 " + config.at("newClient") + "\n";
}

std::string FTP::user(std::string user, Client *cl) {
    cl->last_command = "USER";
    cl->last_command_param = user;
    return "331 " + config.at("passRequired") + "\n";
}

std::string FTP::pass(std::string pass, Client *cl) {
    std::string message;
    if (config.at("user") == cl->last_command_param &&
        config.at("password") == pass) {
        cl->login();
        message = "230 " + config.at("loginSuccess");
    } else {
        message = "530 " + config.at("loginFailed");
    }
    cl->last_command = "";
    cl->last_command_param = "";
    return message + "\n";
}

std::string FTP::syst(Client *cl) {
    if (!cl->isLoggedIn()) return clientNotLogged(cl);
    return "215 " + config.at("systemInfo") + "\n";
}

std::string FTP::list(Client *cl) {
    if (!cl->isLoggedIn()) return clientNotLogged(cl);
    std::string response = "150 " + config.at("listBegin") + "\n";
    for (std::set<std::string>::iterator it = directories.begin();
        it != directories.end(); it++) {
        std::string line = "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 "
            + *it + "\n";
        response += line;
    }
    response += "226 " + config.at("listEnd") + "\n";
    return response;
}

std::string FTP::help(Client *cl) {
    if (!cl->isLoggedIn()) return clientNotLogged(cl);
    return "214 " + config.at("commands") + "\n";
}

std::string FTP::pwd(Client *cl) {
    if (!cl->isLoggedIn()) return clientNotLogged(cl);
    return "257 " + config.at("currentDirectoryMsg") + "\n";
}

std::string FTP::mkd(std::string direc, Client *cl) {
    if (!cl->isLoggedIn()) return clientNotLogged(cl);
    if (directories.exist(direc)) {
        return "550 " + config.at("mkdFailed") + "\n";
    } else {
        directories.add(direc);
        return "257 \"" + direc + "\" " + config.at("mkdSuccess") + "\n";
    }
}

std::string FTP::rmd(std::string direc, Client *cl) {
    if (!cl->isLoggedIn()) return clientNotLogged(cl);
    if (directories.remove(direc) == 1) {
        return "250 \"" + direc + "\" " + config.at("rmdSuccess") + "\n";
    } else {
        return "550 " + config.at("rmdFailed") + "\n";
    }
}

std::string FTP::quit() {
    return "221 " + config.at("quitSuccess") + "\n";
}

std::string FTP::clientNotLogged(Client *cl) {
    cl->last_command = "";
    cl->last_command_param = "";
    return "530 " + config.at("clientNotLogged") + "\n";
}

FTP::~FTP() {
    for (std::map<int, Client*>::iterator it = clients.begin();
        it != clients.end(); it++) {
        delete (*it).second;
    }
}
