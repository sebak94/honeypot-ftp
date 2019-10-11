#ifndef __COMMAND_FACTORY_H__
#define __COMMAND_FACTORY_H__

#include "server_command.h"
#include <string>
#include <map>
#include <memory>

class CommandFactory {
    public:
    static std::shared_ptr<Command> GetCommand(std::string command_name,
        std::map<std::string, std::string> config);
};

#endif
