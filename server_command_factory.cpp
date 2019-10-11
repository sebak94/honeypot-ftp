#include "server_command_factory.h"
#include "server_command.h"
#include "server_quit_command.h"
#include "server_user_command.h"
#include "server_pass_command.h"
#include "server_syst_command.h"
#include "server_list_command.h"
#include "server_help_command.h"
#include "server_pwd_command.h"
#include "server_mkd_command.h"
#include "server_rmd_command.h"
#include "server_unknown_command.h"
#include <string>
#include <map>
#include <memory>

std::shared_ptr<Command> CommandFactory::GetCommand(std::string command_name,
    std::map<std::string, std::string> config) {
    if (command_name == "QUIT")
        return std::shared_ptr<QuitCommand> (new QuitCommand(config));
    if (command_name == "USER")
        return std::shared_ptr<UserCommand> (new UserCommand(config));
    if (command_name == "PASS")
        return std::shared_ptr<PassCommand> (new PassCommand(config));
    if (command_name == "SYST")
        return std::shared_ptr<SystCommand> (new SystCommand(config));
    if (command_name == "LIST")
        return std::shared_ptr<ListCommand> (new ListCommand(config));
    if (command_name == "HELP")
        return std::shared_ptr<HelpCommand> (new HelpCommand(config));
    if (command_name == "PWD")
        return std::shared_ptr<PwdCommand> (new PwdCommand(config));
    if (command_name == "MKD")
        return std::shared_ptr<MkdCommand> (new MkdCommand(config));
    if (command_name == "RMD")
        return std::shared_ptr<RmdCommand> (new RmdCommand(config));
    return std::shared_ptr<UnknownCommand> (new UnknownCommand(config));
}
